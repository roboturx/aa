#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
       QLabel *lab1 = new QLabel("Label1");
       QLabel *lab2 = new QLabel("Label2");
       TContainer *con1 = new TContainer(this, QPoint(10, 10), lab1);
       TContainer *con2 = new TContainer(this, QPoint(20, 50),lab2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
