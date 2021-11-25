#ifndef DIRTREEMODEL_H
#define DIRTREEMODEL_H
#include <QAbstractItemModel>
#include <vector>
#include "myLib/onedirorfileclass.h"
#include <QDir>
#include <QIcon>
#include "myLib/onedirorfileclass.h"
#include "myLib/filedirdata.h"
#include <QFileIconProvider>

enum Columns //перечисление колонок  TreeView
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

    QModelIndex index(int row, int column, const QModelIndex &parent) const;  //возвращает объект элемент модели данных по пересечению его строки и столбца относительно родительского
    QModelIndex parent(const QModelIndex &child) const;                       //возвращает родителя для переданного в параметре элемента  модели данных

    int rowCount(const QModelIndex &parent) const;                             //возвращает номер строки родителя для переданного в параметре элемента  модели данных(относительно родителя)
    int columnCount(const QModelIndex &parent) const;                           //возвращает количество столбцов модели данных

    QVariant data(const QModelIndex &index, int role) const;                    //возвращает данные содержащиеся в элементе модели данных в зависимости от указанной в параметре роли
    QVariant headerData(int section, Qt::Orientation orientation, int role) const; //возвращает имя колонки

    bool canFetchMore(const QModelIndex &parent) const;                             //проверяет есть ли у элемента модели данных дочерние элементы
    void fetchMore(const QModelIndex &parent);                                      // заполняет элемент модели данных дочерними элементами
    void fetchSubDirs(const QModelIndex &parent);                                   //если с элементом модели данных ассоциирован элемент файловой системы и это элемент файловой системы - каталог, получаем подкаталоги
    void fetchZip(const QModelIndex &parent);                                       //если с элементом модели данных ассоциирован элемент файловой системы и это элемент файловой системы - zip файл, получаем содержимое

    Qt::ItemFlags flags(const QModelIndex &index) const;                            //флаги элемента модели данных

    bool hasChildren(const QModelIndex &parent) const;                              //возвращает признак наличия дочерних элементов у переданного в параметрах элемента модели данных


private:

    std::vector<OneDirOrFileClass*>* fileStructure=new std::vector<OneDirOrFileClass*>();   //указатель на вектор содержащий элементы корневого каталога файловой системы
   int findRow(const OneDirOrFileClass* oneDirOrFile) const ;

};

#endif // DIRTREEMODEL_H
