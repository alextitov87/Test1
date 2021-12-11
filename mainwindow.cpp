#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include<QLabel>
#include <QTreeView>
#include <iostream>
#include <dirtreemodel.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->resize(1000, 600);
    QWidget *root_Widget = new QWidget();
    this->setCentralWidget(root_Widget);
    auto currentFileSystem = new DirTreeModel();
    tree=new QTreeView(root_Widget);
    tree->resize(980, 580);
    tree->move(10, 10);
    tree->setModel(currentFileSystem);
    tree->setColumnWidth(NameColumn, 400);
    tree->setColumnWidth(ModificationDateColumn, 200);
    tree->setColumnWidth(TypeColumn, 100);

};

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   tree->resize(this->window()->width() - 20, this->window()->height() - 20);
}

MainWindow::~MainWindow()
{

}

