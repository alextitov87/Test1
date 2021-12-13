#ifndef FILEDIRDATA_H
#define FILEDIRDATA_H
#include "onedirorfileclass.h"
#include "../minizip/mz.h"
#include "../minizip/mz_os.h"
#include "../minizip/mz_strm.h"
#include "../minizip/mz_strm_buf.h"
#include "../minizip/mz_strm_split.h"
#include "../minizip/mz_zip.h"
#include "../minizip/mz_zip_rw.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <sys/stat.h>
#include <ctime>
#include <locale>
#include "rustextrecoderclass.h"


void getRoot(std::vector<OneDirOrFileClass*>* dirs);

std::vector<OneDirOrFileClass*>* expandDir(OneDirOrFileClass* currentDir);

int  expandZipFile(OneDirOrFileClass* zipFile);

std::string wstringToString(const std::wstring& wstr);

std::wstring stringToWstring(const std::string& str);
std::wstring stringToWstring_(const std::string &s);


char* wstringToChar(const std::wstring &wStr);



#endif
