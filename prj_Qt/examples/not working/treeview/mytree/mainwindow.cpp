#include <QTreeView>

#include "mainwindow.h"
#include "mytreemodel.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    QTreeView *myView = new QTreeView(this);
    MyTreeModel *model = new MyTreeModel(this);
    
    
    myView->setModel (model);
   myView->show ();
}

MainWindow::~MainWindow()
{
    
}

