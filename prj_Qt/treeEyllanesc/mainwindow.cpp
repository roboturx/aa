#include "mainwindow.h"
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //db = new dBase ;
   // treemodel = new hC_TreeModel;

    QSortFilterProxyModel proxymodel;
   // proxymodel.setSourceModel(treemodel);
    QTreeView w;
  //  QStandardItemModel* mystdmodel=modelle ();
    qDebug()<< &stdmodel;
    w.setModel(stdmodel);
      w.setWindowTitle ("mainwind treemodel");
    w.expandAll();
      QWidget *aa = new QWidget(this);

    QGridLayout aal(aa);
      aal.addWidget (&w,0,0);
    setCentralWidget (aa);
      aa->show ();
}

MainWindow::~MainWindow()
{
}

