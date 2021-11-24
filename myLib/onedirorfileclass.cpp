#include "myLib/onedirorfileclass.h"
#include <string>
#include <vector>
#include <QDebug>





    OneDirOrFileClass::OneDirOrFileClass(std::wstring _name, DirObjectType dirObjectType,unsigned long long _fileSize, OneDirOrFileClass *_parent)
    {

        shortName=_name;
        type=dirObjectType;
        parent=_parent;
        fileSize=_fileSize;
        fileSizeCompress=_fileSize;


    }

    OneDirOrFileClass::~OneDirOrFileClass()
    {
        //delete fullPath;
        for (OneDirOrFileClass* elem :*children)
            delete elem;
        children->clear();
    }

    std::wstring OneDirOrFileClass::getFullPath() const
    {

        if(parent!=nullptr)
            return parent->getFullPath()+L"//"+shortName;
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

    void OneDirOrFileClass::setPath(std::wstring _path)
    {
        fullPath=_path;
    }

    std::vector<OneDirOrFileClass*>* OneDirOrFileClass::getChildren() const
    {
        //qDebug() << "getChildren";
        return  children;
    }

    void OneDirOrFileClass::addChildren(OneDirOrFileClass* _child)
    {
        children->insert(children->end(),_child);
    }

    void OneDirOrFileClass::clearParent()
    {
        parent=nullptr;
    }

    OneDirOrFileClass* OneDirOrFileClass::getParent() const
    {
        //qDebug() << "getParent() parent=" << parent ;

        return parent;
    }

    void OneDirOrFileClass::setInspected(bool _inspected)
    {
        inspected=_inspected;
    }

    void OneDirOrFileClass::setDateOfUpdate(std::wstring newDateUpdate)
    {
        dateLastUpdate=newDateUpdate;
    }

    void OneDirOrFileClass::setCompressedFileSize(long long compressed)
    {
        fileSizeCompress=compressed;
    }

    bool OneDirOrFileClass::isInspected() const
    {
        return inspected;
    }

    bool OneDirOrFileClass::operator ==(const OneDirOrFileClass& another) const //перегрузка оператора проверки на равенство
    {
        bool r = this->fullPath == another.fullPath; //текущий структура  равена сравниваемой

        return r;
    }

    bool OneDirOrFileClass::operator ==(const OneDirOrFileClass* another) const //перегрузка оператора проверки на равенство
    {
        bool r = this->fullPath == another->fullPath; //текущий структура  равена сравниваемой

        return r;
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
