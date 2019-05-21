#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_2->setCheckable (true);
    QHoverSensitiveButton *xx =
            new QHoverSensitiveButton(this);
    xx->setText("ddddddd");
    xx->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked(bool checked)
{
    if (checked)
       ui->pushButton_2->setText("ddddvfdsvddd");;
}
