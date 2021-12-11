#include "myLib/onedirorfileclass.h"





    OneDirOrFileClass::OneDirOrFileClass(std::wstring _name, DirObjectType dirObjectType,unsigned long long _fileSize, OneDirOrFileClass *_parent)
    {
        shortName = _name;
        type = dirObjectType;
        parent = _parent;
        fileSize = _fileSize;
        fileSizeCompress = _fileSize;
    }

    OneDirOrFileClass::~OneDirOrFileClass()
    {       
        for (OneDirOrFileClass* elem :*children)
            delete elem;
        children->clear();
    }

    std::wstring OneDirOrFileClass::getFullPath() const
    {
        if(parent != nullptr)
            return parent->getFullPath() + L"/" + shortName;
        return shortName;

    }

    std::wstring OneDirOrFileClass::getShortName() const
    {
        return shortName;
    }

    std::wstring OneDirOrFileClass::getDateUpdate() const
    {
        return dateLastUpdate;
    }

    std::vector<OneDirOrFileClass*>* OneDirOrFileClass::getChildren() const
    {        
        return  children;
    }

    void OneDirOrFileClass::addChildren(OneDirOrFileClass* _child)
    {
        children->insert(children->end(),_child);
    }

    void OneDirOrFileClass::clearParent()
    {
        parent = nullptr;
    }

    OneDirOrFileClass* OneDirOrFileClass::getParent() const
    {
       return parent;
    }

    void OneDirOrFileClass::setInspected(bool _inspected)
    {
        inspected = _inspected;
    }

    void OneDirOrFileClass::setDateOfUpdate(std::wstring newDateUpdate)
    {
        dateLastUpdate = newDateUpdate;
    }

    void OneDirOrFileClass::setUncompressedFileSize(long long uncompressed)
    {
        fileSize = uncompressed;
    }

    void OneDirOrFileClass::setCompressedFileSize(long long compressed)
    {
        fileSizeCompress = compressed;
    }

    bool OneDirOrFileClass::isInspected() const
    {
        return inspected;
    }

    DirObjectType OneDirOrFileClass::getType() const
    {
        return type;
    }

   unsigned long long OneDirOrFileClass::getFileSize() const
   {
       return fileSize;
   }

    unsigned long long OneDirOrFileClass::getCompressedFileSize() const
    {
        return fileSizeCompress;
    }
