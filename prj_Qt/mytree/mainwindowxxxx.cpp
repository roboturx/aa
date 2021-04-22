#include "mainwindowxxxx.h"
#include "ui_mainwindowxxxx.h"

MainWindowxxxx::MainWindowxxxx(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowxxxx)
{
    ui->setupUi(this);
}

MainWindowxxxx::~MainWindowxxxx()
{
    delete ui;
}
