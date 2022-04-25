#include "mainwindow.h"
#include <QSortFilterProxyModel>
#include <QTableView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), hC_TreeModel()
{
    db = new dBase ;

    QTreeView *treeView = new QTreeView(this);
   // hC_TreeModel *sourceModel = new hC_TreeModel(this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();

    proxyModel->setSourceModel(trmodel);

    treeView->setModel(proxyModel);
    treeView->expandAll();
    setCentralWidget(treeView);


}

MainWindow::~MainWindow()
{
}

