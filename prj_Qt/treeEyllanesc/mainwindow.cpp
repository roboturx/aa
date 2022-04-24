#include "mainwindow.h"
#include <QSortFilterProxyModel>
#include <QTableView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //db = new dBase ;
   // treemodel = new hC_TreeModel;

    QSortFilterProxyModel proxymodel;
   // proxymodel.setSourceModel(treemodel);
    QTreeView w;
    QStandardItemModel* mystdmodel=modelle ();

    w.setModel(mystdmodel);
    w.expandAll();

}

MainWindow::~MainWindow()
{
}

