

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqltreemodel.h"
#include "database.h"
#include <QSqlQueryModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Mainwindow Database";
    DataBase db;
    
    //db= QSqlDatabase::database();
    QSqlQueryModel *model1 = new QSqlQueryModel(this);
    // model1->setQuery("SELECT id_category, name
    //                      FROM category ca
    //                      WHERE ca.id_parent=0",db);
    model1->setQuery("SELECT h_kod,h_ad,h_acklm FROM h_snf "
                     "WHERE h_prnt = 0",db);
    SqlTreeModel *pepe = new SqlTreeModel();
    pepe->appendModel(model1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    // model->setQuery("SELECT id_category, id_parent, name "
    //                 "FROM category ca
    //                    WHERE ca.id_parent=1",db);
    model->setQuery("SELECT h_kod, h_prnt, h_ad, h_acklm "
                    "FROM h_grp WHERE h_prnt=1",db);
    pepe->appendModel(model);;
    ui->treeView->setModel(pepe);


}

MainWindow::~MainWindow()
{
    delete ui;
}

