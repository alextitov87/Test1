#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <windows.h>
#include "onedirorfileclass.h"
#include "filedirdata.h"
#include <QDebug>

std::wstring stringToWstring(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

void getRoot(std::vector<OneDirOrFileClass*>* dirs)
{
  // qDebug()<<"getRoot-0";
    char buf[26];
	std::vector<std::wstring>* devices=new std::vector<std::wstring>();
    GetLogicalDriveStringsA(sizeof(buf),buf);
    //qDebug()<<"getRoot-1";
    for(char *s=buf; *s; s+=strlen(s)+1)
	{
        std::string buff_s(s);
       // qDebug()<<"getRoot-2 "<<s2ws(buff_s);

        dirs->insert(dirs->end(),  new OneDirOrFileClass(stringToWstring(buff_s),ItIsDriver,0,nullptr));

	}
      
     delete devices;

 
}

std::wstring toWS(DWORD n)
{
    std::wstring num=std::to_wstring(n);
    return num.length()<2 ? L"0"+num: num;
}

std::vector<OneDirOrFileClass*>* expandDir(OneDirOrFileClass *currentDir)
{
    std::vector<OneDirOrFileClass*>* dirs=new std::vector<OneDirOrFileClass*>();
    WIN32_FIND_DATA  fileData;
    HANDLE fileHandle;
    std::wstring currentDirPath=currentDir->getFullPath()+L"\\*";
    qDebug()<<"currentDirPath="<<currentDirPath;
    fileHandle = FindFirstFileW(currentDirPath.c_str(), &fileData);
    if ( fileHandle != INVALID_HANDLE_VALUE )
    {
        do
        {
            DirObjectType currentObjectType=ItIsNotDiscover;
            std::wstring currentObjectName=fileData.cFileName;
            if(currentObjectName==L"." || currentObjectName==L"..")
                continue;
            std::wstring currentObjectExtencion=currentObjectName.substr(currentObjectName.find_last_of(L".") + 1);
            std::transform(currentObjectExtencion.begin(), currentObjectExtencion.end(), currentObjectExtencion.begin(),
                []( wchar_t c){ return std::tolower(c); });

            if((fileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)>0)
                currentObjectType=ItIsDir;
             else if (currentObjectExtencion==L"zip")
            {
               currentObjectType=ItIsZipFile;
            }
            else
                currentObjectType=ItIsFile;
            OneDirOrFileClass* newNode=new OneDirOrFileClass(currentObjectName, currentObjectType, (fileData.nFileSizeHigh * (MAXDWORD+1)) + fileData.nFileSizeLow ,currentDir);
            SYSTEMTIME newNodeTimeUpdate;
            FileTimeToSystemTime(&fileData.ftLastWriteTime,&newNodeTimeUpdate);
            newNode->setDateOfUpdate(toWS(newNodeTimeUpdate.wDay)+L"/"+toWS(newNodeTimeUpdate.wMonth)
                                     +L"/"+toWS(newNodeTimeUpdate.wYear)+L"  "+toWS(newNodeTimeUpdate.wHour)+L":"+
                                     toWS(newNodeTimeUpdate.wMinute)+L":"+toWS(newNodeTimeUpdate.wSecond));
            dirs->insert(dirs->end(), newNode);
        } while( FindNextFileW(fileHandle, &fileData) );
        FindClose(fileHandle);
    }

    currentDir->setInspected(true);

    return dirs;

}