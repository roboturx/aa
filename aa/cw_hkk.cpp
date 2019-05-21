#include "cw_hkk.h"
#include "ui_cw_hkk.h"

CW_hkk::CW_hkk (QWidget *parent) : QDialog(parent),
    ui(new Ui::CW_hkk){

    ui->setupUi(this);
    this->setWindowTitle("Uygulama Hakkında");
    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

CW_hkk::~CW_hkk()
{
    delete ui;
}

void CW_hkk::on_btnOK_clicked()
{
    this->close();
}
void CW_hkk::on_btnOK_2_clicked()
{
    this->close();
}
