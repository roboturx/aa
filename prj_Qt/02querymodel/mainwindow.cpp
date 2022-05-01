
#include <QGridLayout>
#include <QLabel>
#include <QSplitter>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    editableModel = new EditableSqlModel;
    initializeModel(editableModel);

    QSplitter spl;

    QTableView *view = new QTableView;
    view->setModel(editableModel);

    QGridLayout* grly = new QGridLayout;
    mainwdgt = new QWidget;
    grly->addWidget (new QLabel("editable sql model--------------"),0,0,1,1);
    grly->addWidget (new QLabel("editable sql model 2---------------"),0,1,1,1);
    grly->addWidget (view,1,0,1,2);
    mainwdgt->setLayout (grly);
     spl.addWidget (mainwdgt);

    setCentralWidget (mainwdgt);
    mainwdgt->show ();

}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeModel(QSqlQueryModel *model)
{
    model->setQuery("select * from person");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}


