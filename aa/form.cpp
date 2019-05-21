#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QSqlRelationalTableModel *mdl = new QSqlRelationalTableModel(this);
    mdl->setTable ("dbtb_mkn");

    mdl->setRelation (mdl->fieldIndex ("mkn_cinsi"),
                      QSqlRelation("dbtb_cins","id_mkcins","cinsi"));
 mdl->setJoinMode (QSqlRelationalTableModel::LeftJoin );
    mdl->select ();
    ui->tableView->setModel (mdl);
    ui->tableView->setFocus ();
    ui->tableView->setItemDelegate ( new QSqlRelationalDelegate(this));
   // QDataWidgetMapper *mpp= new QDataWidgetMapper(this);
   // mpp->addMapping (ui->comboBox,mdl->fieldIndex ("mkn_cinsi"));
}

Form::~Form()
{
    delete ui;
}
