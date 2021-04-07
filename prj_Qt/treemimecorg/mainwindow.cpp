

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqltreemodel.h"

#include <QSqlQueryModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db= QSqlDatabase::database();
    QSqlQueryModel *model1 = new QSqlQueryModel(this);
    model1->setQuery("SELECT id_category, name FROM category ca WHERE ca.id_parent=0",db);
    SqlTreeModel *pepe = new SqlTreeModel();
    pepe->appendModel(model1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id_category, id_parent, name FROM category ca WHERE ca.id_parent=1",db);
    pepe->appendModel(model);;
    ui->treeView->setModel(pepe);


}

MainWindow::~MainWindow()
{
    delete ui;
}

