#ifndef ONEDIRORFILECLASS_H
#define ONEDIRORFILECLASS_H
#include <string>
#include <vector>
#include <QString>




enum DirObjectType // множество типов элементов файловой системы в рамках модели
{
    ItIsNotDiscover, //тип файловой системы не определен
    ItIsDir,         //это каталог
    ItIsDriver,      //это диск
    ItIsFile,        //это файл
    ItIsZipFile,     //это zip файл
    ItIsZipInnerFile, //это файл содержащийся в zip файле
    ItIsZipInnerDir   //это каталог содержащийся в zip файле
};

class OneDirOrFileClass //класс один объект которого ассоциируется с одним элементом файловой системы (диском, каталогом, файлом)

{
  public:
    OneDirOrFileClass(std::wstring _name, DirObjectType dirObjectType, unsigned long long _fileSize, OneDirOrFileClass *_parent=0);
    ~OneDirOrFileClass();
    std::wstring getFullPath() const;  //возвращает полный путь от корневого каталога
    std::wstring getShortName() const; //возвращает имя элемента файловой системы
    QString getDisplayedName() const;
    std::wstring getDateUpdate() const;//возвращает время последней модификации элемента файловой системы ассоциированного с данным объектом
    std::vector<OneDirOrFileClass*>* getChildren() const;// указатель на вектор с указателями на дочерние объекты данного объекта файловой системы(подкаталоги)
    void addChildren(OneDirOrFileClass* _child);        //добовляет одного потомка
    void clearParent();                                 //обнуляет указатель на объект родитель данного объекта
    OneDirOrFileClass* getParent() const;               // возвращает ссылку на объект родителя
    void setDateOfUpdate(std::wstring newDateUpdate);   // устанавливает время последней модификации ассоциированного с данным объектом реального элемента файловой системы
    void setUncompressedFileSize(long long uncompressed); // устанавливает не сжатый размер файла содержащегося в zip архиве
    void setCompressedFileSize(long long compressed);   // устанавливает сжатый размер файла содержащегося в zip архиве
    void setInspected(bool _inspected);                 //устанавливает флаг факта проверки элемента файловой системы ассоциированного с данным объектом на наличие дочерних элементов(подкаталогов)
    bool isInspected() const;                           // показывает проверялся ли элемент файловой системы ассоциированный с данным объектом на наличие дочерних элементов(подкаталогов)
    DirObjectType getType() const;                      //возвращает тип элемента файловой системы ассоциированного с данным объектом
//    bool operator ==(const OneDirOrFileClass& another) const ; //перегрузка оператора сравнения
//    bool operator ==(const OneDirOrFileClass* another) const ;
    unsigned long long getFileSize() const;             //возвращает размер элемента файловой системы ассоциированного с данным объектом, если элемент файл или содержимое zip файла
    unsigned long long getCompressedFileSize() const;   //возвращает сжатый размер элемента файловой системы ассоциированного с данным объектом, если элемент содержимое zip файла
  private:
    std::wstring shortName;                             //Имя элемента файловой системы ассоциированного с данным объектом
    QString displayedName;
    std::wstring dateLastUpdate=L"";                    //время последней модификации элемента
    unsigned long long fileSize=0;                      //размер файла
    unsigned long long fileSizeCompress=0;              //размер сжатого файла
    mutable std::vector<OneDirOrFileClass*>* children=new std::vector<OneDirOrFileClass*>(); //список дочерних объектов (подкаталоги или содержимое zip файла)
    OneDirOrFileClass *parent=0;                                                             // указатель на родительский объект
    bool inspected = false;                                                                 //флаг показывающий проверялся ли элемент файловой системы на наличие содержимого
    DirObjectType type=ItIsNotDiscover;                                                     //тип элемента файловой системы ассоциированного с объектом

};
#endif
