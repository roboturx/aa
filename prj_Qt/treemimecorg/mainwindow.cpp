

#include "mainwindow.h"
#include "database.h"
#include "sqltreemodel.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Mainwindow Database";
    DataBase db;
    QSqlQuery q;
    if (!q.exec("PRAGMA foreign_keys = ON"))
        qDebug() << q.lastError().text();
    else
        qDebug() << "PRAGMA foreign_keys = ON";
    
    // tree model
    SqlTreeModel *treeModel = new SqlTreeModel(ui->treeView);
    
    
    
    
    // table 1
   
    QSqlQueryModel *model_1 = new QSqlQueryModel(treeModel);
    model_1->setQuery("SELECT h_kod, h_prnt, h_ad,h_acklm "
                      "FROM h_snf "
                      );
    model_1->setHeaderData(0, Qt::Horizontal, tr("Kod"));
    model_1->setHeaderData(1, Qt::Horizontal, tr("Parent"));
    
    ui->tableView->setModel(model_1);
    


    // table 2
    QSqlQueryModel *model_2 = new QSqlQueryModel(treeModel);
    model_2->setQuery("SELECT h_kod, h_prnt, h_ad, h_acklm "
                      "FROM h_grp "
                      /*"WHERE h_prnt=1"*/);
    model_2->setHeaderData(0, Qt::Horizontal, tr("Kod"));
    model_2->setHeaderData(1, Qt::Horizontal, tr("Parent"));
    
    ui->tableView_2->setModel(model_2);
    



    // table 3
    QSqlQueryModel *model_3 = new QSqlQueryModel(treeModel);
    model_3->setQuery("SELECT * "
                      "FROM h_hsp "
                      /*"WHERE h_prnt=10"*/);
    model_3->setHeaderData(0, Qt::Horizontal, tr("Kod"));
    model_3->setHeaderData(1, Qt::Horizontal, tr("Parent"));
    
    ui->tableView_3->setModel(model_3);
    

   
    
    ui->treeView->setModel (treeModel);

    treeModel->insertModel(model_1,0);
  //  treeModel->appendModel(model_2);
  //  treeModel->appendModel(model_3);
    
   
    
    qDebug() << "resetted";
}

MainWindow::~MainWindow()
{
    delete ui;
}









//QSqlQueryModel *model1 = new QSqlQueryModel(this);
//// model1->setQuery("SELECT id_category, name
////                      FROM category ca
////                      WHERE ca.id_parent=0",db);
//model1->setQuery("SELECT h_kod, h_prnt, h_ad,h_acklm "
//                 "FROM h_snf "
//                 "WHERE h_prnt = 0",
//                 db);

//QSqlQueryModel *model2 = new QSqlQueryModel(this);
//// model->setQuery("SELECT id_category, id_parent, name "
////                 "FROM category ca
////                    WHERE ca.id_parent=1",db);
//model2->setQuery("SELECT h_kod, h_prnt, h_ad, h_acklm "
//                 "FROM h_grp "
//                 "WHERE h_prnt=1",
//                 db);
//// pepe->appendModel(model);;
//// ui->treeView->setModel(pepe);
//QSqlQueryModel *model3 = new QSqlQueryModel(this);
//// model->setQuery("SELECT id_category, id_parent, name "
////                 "FROM category ca
////                    WHERE ca.id_parent=1",db);
//model3->setQuery("SELECT * "
//                 "FROM h_hsp "
//                 "WHERE h_prnt=10",
//                 db);
