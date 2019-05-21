#include "frmHkk.h"
#include "ui_frmHkk.h"

frmHkk::frmHkk (QWidget *parent) : QDialog(parent),
    ui(new Ui::frmHkk){

    ui->setupUi(this);
    this->setWindowTitle("Uygulama Hakkında");
    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

frmHkk::~frmHkk()
{
    delete ui;
}

void frmHkk::on_btnOK_clicked()
{
    this->close();
}
void frmHkk::on_btnOK_2_clicked()
{
    this->close();
}
