#include "mainwindow.h"

#include <QTableView>
#include <QGridLayout>
#include <QSplitter>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(10,10,800,640);


    qDebug()<<"Main";
    mysqlmodel = new MySqlModel(this);
    qDebug()<<"MyModel";
    QTreeView *soltreeview =new QTreeView(this);
    soltreeview->setModel(mysqlmodel/*->stdmodel*/);
    soltreeview->expandAll();


    QWidget *solwdgt = new QWidget(this);
    QGridLayout *sollyt = new QGridLayout(solwdgt);
    solwdgt->setLayout(sollyt);
    sollyt->addWidget(new QLabel ("Accounting") ,0,0);
    sollyt->addWidget(soltreeview,1,0);
    qDebug()<<"SolTreeView";

    treemodel = new hC_TreeModel;
    qDebug()<<"hctreemodel";

    QTreeView *sagwdgt =new QTreeView(this);
    sagwdgt->setModel(proxymodel);
    proxymodel->setSortRole (Qt::DisplayRole);
    proxymodel->setFilterRegularExpression(
                QRegularExpression("*", QRegularExpression::CaseInsensitiveOption));
    proxymodel->setFilterKeyColumn(0);
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

