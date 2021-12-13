#include "filedirdata.h"



std::wstring toWS(uint32_t n)
{
    std::wstring num = std::to_wstring(static_cast<int>(n));
    return num.length() <2 ? L"0" + num: num;
}

void replaceAll(std::wstring &line, std::wstring findLine, std::wstring replaceOn)
{
    size_t pos;
    while ((pos = line.find(findLine)) != std::string::npos) {
      line.replace(pos, 1, replaceOn);
    }
}

std::vector<std::wstring> splitPath(std::wstring path)
{

    std::vector<std::wstring> pathNodes;
    size_t pos = 0;
    size_t pos_before = 0;
    while((pos = path.find(L"/",pos)) != std::wstring::npos)
    {
        pathNodes.push_back(path.substr(pos_before,pos - pos_before));
        pos = pos + 1;
        pos_before = pos;
    }
    if(pos_before<(path.length() - 1))
        pathNodes.push_back(path.substr(pos_before,path.length() - pos_before));
    return pathNodes;

}

bool findAndInsert(OneDirOrFileClass* currentZipNode, std::vector<std::wstring> &pathParts, int pathNum)
{
    return false;
}

OneDirOrFileClass* insertZipNode(OneDirOrFileClass* currentZipFile, std::wstring zipContent )
{
    std::vector<std::wstring> pathParts;
    std::wstring path = zipContent;
    replaceAll(path, L"\\", L"/");
    pathParts = splitPath(path);
    std::vector<OneDirOrFileClass *> *currentChilds = currentZipFile->getChildren();
    OneDirOrFileClass* parent = currentZipFile;
    for(int i = 0; i < pathParts.size(); i++)
    {
        bool needAppend = true;
        if (currentChilds != nullptr)
            for(int j = 0; j < currentChilds->size(); j++)
                if(pathParts[i] == (*currentChilds)[j]->getShortName())
                {
                    needAppend = false;
                    parent = (*currentChilds)[j];
                    currentChilds = (*currentChilds)[j]->getChildren();
                    j = currentChilds->size();
                }
        if(needAppend)
            for(int k = i; k < pathParts.size(); k++)
            {
                if(k < (pathParts.size()-1))
                {
                    OneDirOrFileClass * currentNode = new OneDirOrFileClass(pathParts[k], ItIsZipInnerDir, 0, parent);
                    currentChilds->push_back(currentNode);
                    parent = currentNode;
                    currentChilds = currentNode->getChildren();
                }
                else
                 if(zipContent[zipContent.length()-1] == L'/')
                 {
                     OneDirOrFileClass * currentNode = new OneDirOrFileClass(pathParts[k], ItIsZipInnerDir, 0, parent);
                     currentChilds->push_back(currentNode);
                     return  currentNode;
                 }
                else
                 {
                     OneDirOrFileClass * currentNode = new OneDirOrFileClass(pathParts[k], ItIsZipInnerFile, 0, parent);
                     currentChilds->push_back(currentNode);
                     return  currentNode;
                 }
            }
    }
    return nullptr;
}

std::string analyzeLine(std::string str)
{
    std::string result="";
    std::string comma="";
    for(int i=0; i<str.length(); i++)
    {
        result+=comma+std::to_string(static_cast<char>(str.at(i)));
        comma=", ";
    }
    return result;
}

int expandZipFile(OneDirOrFileClass* zipFile)
{
    mz_zip_file *file_info = NULL;
    uint32_t ratio = 0;
    int32_t err = MZ_OK;
    struct tm tmu_date;
    const char *method = NULL;
    char crypt = ' ';
    void *reader = NULL;
    const char *path = wstringToChar(zipFile->getFullPath());
    mz_zip_reader_create(&reader);
    err = mz_zip_reader_open_file(reader, path);

    if (err != MZ_OK) {        
        mz_zip_reader_delete(&reader);
        return err ;
    }    
    err = mz_zip_reader_goto_first_entry(reader);
    if (err != MZ_OK && err != MZ_END_OF_LIST) {        
        mz_zip_reader_delete(&reader);
        return err;
    }
    do {
        err = mz_zip_reader_entry_get_info(reader, &file_info);
        if (err != MZ_OK) {
            break;
        }
        mz_zip_time_t_to_tm(file_info->modified_date, &tmu_date);
        std::wstring moddifedtime = toWS((uint32_t)tmu_date.tm_mday) + L"/" + toWS((uint32_t)tmu_date.tm_mon) + L"/" + toWS((uint32_t)tmu_date.tm_year-100+2000) + L"  "
                + toWS((uint32_t)tmu_date.tm_hour) + L":" + toWS((uint32_t)tmu_date.tm_min) + L":" + toWS((uint32_t)tmu_date.tm_sec);
        std::wstring fileName = stringToWstring_(file_info->filename);

        {
               OneDirOrFileClass* zipNode = insertZipNode(zipFile,stringToWstring_(file_info->filename));
               if(zipNode != nullptr)
               {
                    zipNode->setDateOfUpdate(moddifedtime);
                    zipNode->setUncompressedFileSize(file_info->uncompressed_size);
                    zipNode->setCompressedFileSize(file_info->compressed_size);
                    std::string filename(file_info->filename);
               }
        }
        err = mz_zip_reader_goto_next_entry(reader);
        if (err != MZ_OK && err != MZ_END_OF_LIST) {

            break;
        }
    } while (err == MZ_OK);
    mz_zip_reader_delete(&reader);
    return MZ_OK;

}


