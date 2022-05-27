#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ekranayaz();


    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::ekranayaz);

    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::sil);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ekranayaz()
{
    if (ui->checkBox->isChecked() )
    {
        ui->burayayaz->setText(" ne yazalım  CHECKED");
    }
    else
    {
        ui->burayayaz->setText(" bişey yazmayalım NOT CHECJKED ");
    }
}

void MainWindow::sil()
{
    ui->burayayaz->setText(" ******************************* ");
}

