#include "dirtreemodel.h"
#include <vector>
#include <QDir>
#include <QIcon>
#include "myLib/onedirorfileclass.h"
#include "myLib/filedirdata.h"
#include <QFileIconProvider>

DirTreeModel::DirTreeModel(QObject *parent ):
    QAbstractItemModel(parent)
{
    getRoot(fileStructure);
}

DirTreeModel::~DirTreeModel()
{
    fileStructure->clear();
}

QModelIndex DirTreeModel::index(int row, int column, const QModelIndex &parent) const
{  
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    if (!parent.isValid()) {
        return createIndex(row, column, (*fileStructure)[row]);
    }  
    OneDirOrFileClass* parentInfo = static_cast<OneDirOrFileClass*>(parent.internalPointer());
    return createIndex(row, column, (*parentInfo->getChildren())[row]);
}

QModelIndex  DirTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }
    OneDirOrFileClass* childInfo = static_cast<OneDirOrFileClass*>(child.internalPointer());
    OneDirOrFileClass* parentInfo = childInfo->getParent();
    if (parentInfo != 0) {
        if(parentInfo->test!=10)
            return QModelIndex();
        return createIndex(findRow(parentInfo), RamificationColumn, parentInfo);
    }
    else {
        return QModelIndex();
    }
}

int DirTreeModel::findRow(const OneDirOrFileClass *oneDirOrFile) const
{    
    const std::vector<OneDirOrFileClass*>* parentInfoChildren = oneDirOrFile->getParent() != 0 ? oneDirOrFile->getParent()->getChildren(): fileStructure;//получаем соседей
    const std::vector<OneDirOrFileClass*>::const_iterator position = std::find(parentInfoChildren->begin(),parentInfoChildren->end(), oneDirOrFile);//ищем позицию искомого элемента в списке его соседей
    return std::distance(parentInfoChildren->begin(), position);
}

int  DirTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return fileStructure->size();
    }
    const OneDirOrFileClass* parentInfo = static_cast<const OneDirOrFileClass*>(parent.internalPointer()); //получаем указатель на ассоциированный с объектом элемент файловой системы
    Q_ASSERT(parentInfo != 0);

    return parentInfo->getChildren()->size();
}
int  DirTreeModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
    return 5;
}

QVariant  DirTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    const OneDirOrFileClass* oneDirOrFile = static_cast<OneDirOrFileClass*>(index.internalPointer());
    switch (index.column()) {
    case NameColumn:
        if(role==Qt::DecorationRole)
        {
            QFileIconProvider p;
            if(oneDirOrFile->getType()==ItIsDir)
                return p.icon(QFileIconProvider::Folder);
            if(oneDirOrFile->getType()==ItIsDriver)
                return p.icon(QFileIconProvider::Drive);
            return p.icon(QFileIconProvider::File);
        }
        if(role==Qt::DisplayRole)
            return (QVariant) QString::fromWCharArray(oneDirOrFile->getShortName().c_str());
    case SizeColumn:
        if (role == Qt::DisplayRole) {
            return oneDirOrFile->getType()==ItIsFile || oneDirOrFile->getType()==ItIsZipInnerFile ? QVariant(oneDirOrFile->getFileSize()): QVariant();         }
        break;
    case ModificationDateColumn:
        if (role == Qt::DisplayRole) {
            return (QVariant) QString::fromWCharArray(oneDirOrFile->getDateUpdate().c_str());
        }
        break;
    case SizeCompressedColumn:
        if( role == Qt::DisplayRole)
        {
           return oneDirOrFile->getType()==ItIsZipInnerFile ? QVariant(oneDirOrFile->getCompressedFileSize()): QVariant();
        }
        break;
    case TypeColumn:
        if (role == Qt::DisplayRole) {
            if(oneDirOrFile->getType()==ItIsDir)
                return QVariant("<DIR>");
            if(oneDirOrFile->getType()==ItIsZipFile)
                return QVariant("<ZIP>");
            return QVariant();
        }
        break;
    default:
        break;
    }
    return QVariant();
}

QVariant DirTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    const QStringList headers = {"Имя", "Дата изменения",  "Тип", "Размер", "Сжатый размер"};
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section < headers.size()) {
        return headers[section];
    }
    return QVariant();
}

bool DirTreeModel::canFetchMore(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return false;
    }

    const OneDirOrFileClass* parentInfo = static_cast<const OneDirOrFileClass*>(parent.internalPointer());
    return !parentInfo->isInspected();
}

void DirTreeModel::fetchMore(const QModelIndex &parent)
{    
    Q_ASSERT(parent.isValid());
    OneDirOrFileClass* parentInfo = static_cast<OneDirOrFileClass*>(parent.internalPointer());
    Q_ASSERT(parentInfo != 0);
    Q_ASSERT(!parentInfo->isInspected());
    if(parentInfo->getType()==ItIsDir || parentInfo->getType()==ItIsDriver)
        fetchSubDirs(parent);
    if(parentInfo->getType()==ItIsZipFile)
        fetchZip(parent);
    if(parentInfo->getType()==ItIsFile || parentInfo->getType()==ItIsZipInnerFile)
        {
            beginInsertRows(parent, 0, 0);
            parentInfo->setInspected(true);
            endInsertRows();
        }
}

void DirTreeModel::fetchSubDirs(const QModelIndex &parent)
{
    OneDirOrFileClass* parentInfo = static_cast<OneDirOrFileClass*>(parent.internalPointer());
    std::vector<OneDirOrFileClass*>* expandedDir=expandDir(parentInfo);
    int insrtCnt = expandedDir->size() -1;
    if (insrtCnt < 0) {
           insrtCnt = 0;
      }
       std::vector<OneDirOrFileClass*>* currentChildren= parentInfo->getChildren();
       beginInsertRows(parent, 0, insrtCnt);
       parentInfo->getChildren()->reserve(expandedDir->size());
       for ( OneDirOrFileClass* entry: *expandedDir) {
           currentChildren->insert(currentChildren->end(), entry);
       }
       delete expandedDir;
       parentInfo->setInspected(true);
       endInsertRows();
}

void DirTreeModel::fetchZip(const QModelIndex &parent)
{
     OneDirOrFileClass* parentInfo = static_cast<OneDirOrFileClass*>(parent.internalPointer());
     std::vector<OneDirOrFileClass*>* expandedZip=expandZipFile(parentInfo);
     int insrtCnt=expandedZip->size() - 1;
     if(insrtCnt<0)
     {
         insrtCnt=0;
     }
     std::vector<OneDirOrFileClass*>* currentChildren= parentInfo->getChildren();
     beginInsertRows(parent, 0, insrtCnt);
     parentInfo->getChildren()->reserve(expandedZip->size());
     for (OneDirOrFileClass* subZip: *expandedZip)
         currentChildren->insert(currentChildren->end(),subZip);
     delete expandedZip;
     parentInfo->setInspected(true);
     endInsertRows();
}

Qt::ItemFlags DirTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    return flags;
}

bool DirTreeModel::hasChildren(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        const OneDirOrFileClass* parentInfo = static_cast<const OneDirOrFileClass*>(parent.internalPointer());
        if(parentInfo->getType()==ItIsFile || parentInfo->getType()==ItIsZipInnerFile)
            return false;
        if (!parentInfo->isInspected()) {
            return true;
        }
    }
    return QAbstractItemModel::hasChildren(parent);
}
