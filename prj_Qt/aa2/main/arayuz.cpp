#include "globals.h"
#include "arayuz.h"
#include "ui_arayuz.h"

Arayuz::Arayuz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arayuz)
{
    ui->setupUi(this);
    dbase=new Dbase;
    dbase->setGeometry (20,30,300,480);
    dbase->setWindowTitle("Veri Tabanı Kontrol");
    dbase->show();
}

Arayuz::~Arayuz()
{
    delete ui;
}
