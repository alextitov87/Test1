#ifndef DIRTREEMODEL_H
#define DIRTREEMODEL_H

#include <QAbstractItemModel>

#include <vector>
#include "myLib/onedirorfileclass.h"

enum Columns
{
    RamificationColumn,
    NameColumn = RamificationColumn,
    ModificationDateColumn,
    TypeColumn,
    SizeColumn,
    SizeCompressedColumn,
    ColumnCount
};


class DirTreeModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DirTreeModel(QObject *parent = 0);
    ~DirTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);
    void fetchSubDirs(const QModelIndex &parent);
    void fetchZip(const QModelIndex &parent);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool hasChildren(const QModelIndex &parent) const;


private:
    void setRootDir();




 std::vector<OneDirOrFileClass*>* fileStructure=new std::vector<OneDirOrFileClass*>();

   
   int findRow(const OneDirOrFileClass* oneDirOrFile) const ;

};

#endif // DIRTREEMODEL_H
