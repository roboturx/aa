#include "mainwindow.h"

#include <QTableView>
#include <QGridLayout>
#include <QSplitter>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(510,10,800,640);


    qDebug()<<"Main";
    mysqlmodel = new MySqlModel(this);

    QTreeView *soltreeview =new QTreeView(this);
    soltreeview->setModel(mysqlmodel);
    soltreeview->expandAll();


    QWidget *solwdgt = new QWidget(this);
    QGridLayout *sollyt = new QGridLayout(solwdgt);
    solwdgt->setLayout(sollyt);
    sollyt->addWidget(new QLabel ("Accounting") ,0,0);
    sollyt->addWidget(soltreeview,1,0);
    qDebug()<<"SolTreeView";

    treemodel = new hC_TreeModel;


    QTreeView *sagwdgt =new QTreeView(this);
    sagwdgt->setModel(treemodel->proxymodel);
    treemodel->proxymodel->setSortRole (Qt::DisplayRole);
    treemodel->proxymodel->setFilterRegularExpression(
                QRegularExpression("*", QRegularExpression::CaseInsensitiveOption));
    treemodel->proxymodel->setFilterKeyColumn(0);
    sagwdgt->expandAll();
    qDebug()<<"SağTreeView";

    QSplitter* splitter =new QSplitter(this);
    splitter->addWidget (solwdgt);
    splitter->addWidget (sagwdgt);
    setCentralWidget (splitter);

}
MainWindow::~MainWindow()
{
}

