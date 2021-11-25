#include <dirent.h>
#include "filedirdata.h"

std::wstring stringToWstring_(const std::string &s)
{
   std::wstring wsTmp(s.begin(), s.end());
   return wsTmp;

}


std::wstring stringToWstring(const std::string& str)
{
    std::string curLocale = setlocale(LC_ALL, "");
    const char* _Source = str.c_str();
    size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

void getRoot(std::vector<OneDirOrFileClass*>* dirs)
{

    qDebug() << "getRoot";
    OneDirOrFileClass* root= new OneDirOrFileClass(L"/", ItIsDir, 0, nullptr);
    std::vector<OneDirOrFileClass*>* expandedRoot =  expandDir(root);
   for(int i=0; i<expandedRoot->size(); i++)
   {
        dirs->insert(dirs->end(), new OneDirOrFileClass(L"/"+(*expandedRoot)[i]->getShortName(),ItIsDir,0,nullptr));
        delete (*expandedRoot)[i];
   }
    delete expandedRoot;
 
}



std::vector<OneDirOrFileClass*>* expandDir(OneDirOrFileClass *currentDir)
{
    std::vector<OneDirOrFileClass*>* dirs=new std::vector<OneDirOrFileClass*>();;
    char* currentDirPath=wstringToChar(currentDir->getFullPath());
	struct dirent *entry;
	DIR *dp;
    dp=opendir(currentDirPath);
	if (dp == NULL) 
	{
		return dirs;
	}
	while((entry = readdir(dp)))
	{
        DirObjectType currentObjectType=ItIsNotDiscover;
		std::string fileName(entry->d_name);
        std::wstring currentObjectName=stringToWstring(fileName);
		if(currentObjectName==L"." || currentObjectName==L"..")
			continue;
		std::wstring currentObjectExtencion=currentObjectName.substr(currentObjectName.find_last_of(L".") + 1);
		std::transform(currentObjectExtencion.begin(), currentObjectExtencion.end(), currentObjectExtencion.begin(),
                []( wchar_t c){ return std::tolower(c); });
		
		unsigned long long f_size=0;
		
		std::string dtUpdate="";
		struct stat file_stat;
		std::string dirPath(currentDirPath);
		std::string fullFilePath=dirPath+"/"+fileName;
		
		
		if(stat(fullFilePath.c_str(), &file_stat))		
			currentObjectType=ItIsNotDiscover;
        else 
		{
            char mbstr[100];
            const std::time_t mtime =static_cast<std::time_t>(file_stat.st_mtime);
			std::strftime(mbstr,100,"%Y/%m/%d %T", std::localtime(&mtime));
			dtUpdate=mbstr;
			f_size=static_cast<unsigned long long>(file_stat.st_size);
			if (S_IFDIR==(file_stat.st_mode & S_IFMT))
                currentObjectType=ItIsDir;
			else
            {
				if (currentObjectExtencion==L"zip")
				{
					currentObjectType=ItIsZipFile;
				}
					else
						currentObjectType=ItIsFile;
				}
		}

		OneDirOrFileClass* newNode=new OneDirOrFileClass(currentObjectName, currentObjectType, f_size ,currentDir);
		newNode->setDateOfUpdate(stringToWstring(dtUpdate));
		dirs->insert(dirs->end(), newNode);
		
	}
		
	closedir(dp);
    return dirs;

}


