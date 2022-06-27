#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytreemodel.h"

#include <QDebug>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "classname: " << this->metaObject()->className() ;
    qDebug() << "parent name: " << this->metaObject()->superClass()->className() ;
    qDebug() << "method count" << this->metaObject()->methodCount() ;

    MyTreeModel* model = new MyTreeModel(12,12);
    QTableView* table = new QTableView ;
    table->setModel(model);
    table->show();



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

