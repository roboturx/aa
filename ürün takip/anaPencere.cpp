
#include "anapencere.h"
#include "ui_anapencere.h"
#include "frmGrs.h"

AnaPencere::AnaPencere(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::AnaPencere){
    ui->setupUi(this);
}

AnaPencere::~AnaPencere()
{
    delete ui;
}

void AnaPencere::on_pushButton_clicked()
{
    frmGrs login;
    login.setModal(true);
    login.exec();
}
