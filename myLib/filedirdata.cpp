#include "filedirdata.h"

char* wstringToChar(const std::wstring wStr)
{
    const wchar_t *input = wStr.c_str();
    // Count required buffer size (plus one for null-terminator).
    size_t size = (wcslen(input) + 1) * sizeof(wchar_t);
    char *buffer = new char[size];
    #ifdef __STDC_LIB_EXT1__
        // wcstombs_s is only guaranteed to be available if __STDC_LIB_EXT1__ is defined
        size_t convertedSize;
        std::wcstombs_s(&convertedSize, buffer, size, input, size);
    #else
        std::wcstombs(buffer, input, size);
    #endif
    return buffer;
}

std::string wstringToString(const std::wstring& wstr){
    std::string str((const char*)&wstr[0], sizeof(wchar_t)/sizeof(char)*wstr.size());
    return str;
}




std::wstring toWS(uint32_t n)
{
    std::wstring num=std::to_wstring(static_cast<int>(n));

    return num.length()<2 ? L"0"+num: num;
}

std::vector<OneDirOrFileClass*>* expandZipFile(OneDirOrFileClass* zipFile)
{
    std::vector<OneDirOrFileClass*>* zipFileContaine=new std::vector<OneDirOrFileClass*>();
    mz_zip_file *file_info = NULL;
    uint32_t ratio = 0;
    int32_t err = MZ_OK;
    struct tm tmu_date;
    const char *method = NULL;
    char crypt = ' ';
    void *reader = NULL;
    const char *path=wstringToChar(zipFile->getFullPath());
    mz_zip_reader_create(&reader);
    err = mz_zip_reader_open_file(reader, path);
    if (err != MZ_OK) {
        mz_zip_reader_delete(&reader);
        return zipFileContaine;
    }
    err = mz_zip_reader_goto_first_entry(reader);
    if (err != MZ_OK && err != MZ_END_OF_LIST) {
        mz_zip_reader_delete(&reader);
        return zipFileContaine;
    }
    do {
        err = mz_zip_reader_entry_get_info(reader, &file_info);
        if (err != MZ_OK) {          
            break;
        }
        mz_zip_time_t_to_tm(file_info->modified_date, &tmu_date);
        std::wstring moddifedtime =toWS((uint32_t)tmu_date.tm_mday)+L"/"+toWS((uint32_t)tmu_date.tm_mon)+L"/"+toWS((uint32_t)tmu_date.tm_year-100+2000)+L"  "
                +toWS((uint32_t)tmu_date.tm_hour)+L":"+toWS((uint32_t)tmu_date.tm_min)+L":"+toWS((uint32_t)tmu_date.tm_sec);
        std::wstring fileName=stringToWstring_(file_info->filename);
        if(fileName[fileName.length()-1]!=L'/' && fileName[fileName.length()-1]!=L'\\')
        {
                OneDirOrFileClass* zipNode=new OneDirOrFileClass(stringToWstring_(file_info->filename),ItIsZipInnerFile,file_info->uncompressed_size,zipFile);
                zipNode->setDateOfUpdate(moddifedtime);
                zipNode->setCompressedFileSize(file_info->compressed_size);
                zipFileContaine->insert(zipFileContaine->end(), zipNode);
        }
        err = mz_zip_reader_goto_next_entry(reader);
        if (err != MZ_OK && err != MZ_END_OF_LIST) {

            break;
        }
    } while (err == MZ_OK);

    mz_zip_reader_delete(&reader);

    if (err == MZ_END_OF_LIST)
        return zipFileContaine;

    return zipFileContaine;
}
