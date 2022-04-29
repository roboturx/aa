#include "mainwindow.h"

#include <QTableView>
#include <QGridLayout>
#include <QSplitter>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(10,10,800,640);
    treemodel = new hC_TreeModel;


    mysqlmodel = new MySqlModel(this);

    QTreeView *soltreeview =new QTreeView(this);
    soltreeview->setModel(mysqlmodel);
    soltreeview->expandAll();

    QSplitter* splitter =new QSplitter(this);

    QWidget *solwdgt = new QWidget(this);
    QGridLayout *sollyt = new QGridLayout(solwdgt);
    solwdgt->setLayout(sollyt);

    sollyt->addWidget(new QLabel ("Accountig") ,0,0);
    sollyt->addWidget(soltreeview,1,0);

    QTreeView *sagwdgt =new QTreeView(this);
    sagwdgt->setModel(proxymodel);
    proxymodel->setSortRole (Qt::DisplayRole);
    proxymodel->setFilterRegularExpression(
                QRegularExpression("*", QRegularExpression::CaseInsensitiveOption));
    proxymodel->setFilterKeyColumn(0);

    sagwdgt->expandAll();

    splitter->addWidget (solwdgt);
    splitter->addWidget (sagwdgt);
    setCentralWidget (splitter);

}
MainWindow::~MainWindow()
{
}

