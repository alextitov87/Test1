#ifndef ONEDIRORFILECLASS_H
#define ONEDIRORFILECLASS_H
#include <string>
#include <vector>


enum DirObjectType
{
    ItIsNotDiscover,
    ItIsDir,
    ItIsDriver,
    ItIsFile,
    ItIsZipFile,
    ItIsZpiInnerDir,
    ItIsZipInnerFile
};

class OneDirOrFileClass

{
  public:
    OneDirOrFileClass(std::wstring _name, DirObjectType dirObjectType, unsigned long long _fileSize, OneDirOrFileClass *_parent=0);

    ~OneDirOrFileClass();


    std::wstring getFullPath() const;
    std::wstring getShortName() const;
    std::wstring getDateUpdate() const;

    void setPath(std::wstring _path);

    std::vector<OneDirOrFileClass*>* getChildren() const;

    void addChildren(OneDirOrFileClass* _child);
    void clearParent();

    OneDirOrFileClass* getParent() const;
    void setDateOfUpdate(std::wstring newDateUpdate);
    void setCompressedFileSize(long long compressed);
    void setInspected(bool _inspected);
    bool isInspected() const;
    DirObjectType getType() const;
    bool operator ==(const OneDirOrFileClass& another) const ;
    bool operator ==(const OneDirOrFileClass* another) const ;
    unsigned long long getFileSize() const;
    unsigned long long getCompressedFileSize() const;


    int test =10;
  private:
    std::wstring fullPath;
    std::wstring shortName;
    std::wstring path;
    std::wstring dateLastUpdate=L"";
    unsigned long long fileSize=0;
    unsigned long long fileSizeCompress=0;
    mutable std::vector<OneDirOrFileClass*>* children=new std::vector<OneDirOrFileClass*>();
    OneDirOrFileClass *parent=0;
    bool inspected = false;
    DirObjectType type=ItIsNotDiscover;


};


#endif
