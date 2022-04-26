#include "mainwindow.h"

#include <QTableView>
#include <QGridLayout>
#include <QSplitter>>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), hC_TreeModel()
{

    treemodel = new hC_TreeModel(this);
    QSplitter* splitter =new QSplitter(this);


    QTreeView *w =new QTreeView;
    w->setModel(stdmodel);
    w->setWindowTitle ("mainwind treemodel");
    w->expandAll();


    QTreeView *w2 =new QTreeView;
    w2->setModel(proxymodel);
    proxymodel->setSortRole (Qt::DisplayRole);
    proxymodel->setFilterRegularExpression(
        QRegularExpression("*A", QRegularExpression::CaseInsensitiveOption));
    proxymodel->setFilterKeyColumn(1);

  //  w2->expandAll();

    splitter->addWidget (w);
    splitter->addWidget (w2);
    setCentralWidget (splitter);

}
MainWindow::~MainWindow()
{
}

