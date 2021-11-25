# Test1
Realisation QAbstractItemModel for QTreeView

Описание файлов проекта

myLib/onedirorfileclass.h – заголовочный файл, содержит объявление класса OneDirOrFileClass его переменных и методов. Объект данного класса в модели ассоциирован с каким-либо элементом файловой системы (каталогом, диском, файлом или ZIP файлом). 
myLib/onedirorfileclass.cpp – файл содержит определение методов класса OneDirOrFileClass

myLib/filedirdata.h – заголовочный файл содержит объявления функций необходимых для работы с файловой системой и zip файлами
  getRoot  - функция заполняет модель файловой системы содержимым корневого каталога  в случае UNIX или дисками в случае Windows
  expandDir – функция в качестве параметра получает элемент файловой системы (каталог или файл). Если элемент каталог или zip возвращает указатель на вектор с подкаталогами каталога или содержимым ZIP файла(получаемое с помощью expandZipFile)
  expandZipFile – функция возвращает указатель с содержимым Zip файла

myLib/filedata.cpp – содержит определение функцию  expandZipFile
myLib/filedirdata_win32.cpp – содержит определения функций  getRoot  и expandDir для windows
myLib/filedirdata_posix.cpp – содержит определения функций  getRoot  и expandDir для unix

dirtreemodel.h – заголовочный файл, содержит объявление класса DirTreeModel. Данный класс является классом реализацией древовидной модели данных для QTreeView
dirtreemodel.cpp - файл содержит определение методов класса DirTreeModel

mainwindow.h - заголовочный файл, содержит объявление класса MainWindow
mainwindow.cpp - файл содержит определение методов класса MainWindow

minizip/ - подкаталог содержит файлы фреймворка minizip-ng https://github.com/zlib-ng/minizip-ng
