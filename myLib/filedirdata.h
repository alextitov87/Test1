#ifndef FILEDIRDATA_H
#define FILEDIRDATA_H
#include <string>
#include <vector>
#include "onedirorfileclass.h"

void getRoot(std::vector<OneDirOrFileClass*>* dirs);

std::vector<OneDirOrFileClass*>* expandDir(OneDirOrFileClass* currentDir);

std::vector<OneDirOrFileClass*>*  expandZipFile(OneDirOrFileClass* zipFile);

std::string wstringToString(const std::wstring& wstr);

std::wstring stringToWstring(const std::string& str);

char* wstringToChar(const std::wstring wStr);



#endif
