#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytreemodel.h"

#include <QDebug>
#include <QTableView>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "classname: " << this->metaObject()->className() ;
    qDebug() << "parent name: " << this->metaObject()->superClass()->className() ;
    qDebug() << "method count" << this->metaObject()->methodCount() ;

    QObject root;

    root.setObjectName("root");
    QObject* child;
    QObject* foo = new QObject(&root);
    foo->setObjectName("foo");
    child = new QObject (foo);
    child->setObjectName("Murat");
    child = new QObject (foo);
    child->setObjectName("Murat");
    child = new QObject (foo);
    child->setObjectName("Murat2");
    child = new QObject (foo);
    child->setObjectName("Murat3");

    QObject *bar = new QObject( &root );
    bar->setObjectName( "bar" );


    MyTreeModel model (&root);
    QTreeView* tree = new QTreeView ;
    tree->setModel(&model);
    tree->show();



    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    qDebug() << "clicked";
}

