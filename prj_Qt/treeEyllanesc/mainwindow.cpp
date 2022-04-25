#include "mainwindow.h"

#include <QTableView>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), hC_TreeModel()
{
<<<<<<< HEAD
    db = new dBase ;

    QTreeView *treeView = new QTreeView(this);
   // hC_TreeModel *sourceModel = new hC_TreeModel(this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();

    proxyModel->setSourceModel(trmodel);

    treeView->setModel(proxyModel);
    treeView->expandAll();
    setCentralWidget(treeView);
=======

    treemodel = new hC_TreeModel;
>>>>>>> 1a9f7586759c69f33fda9e4bc57a5bdac72774c7


}

MainWindow::~MainWindow()
{
}

