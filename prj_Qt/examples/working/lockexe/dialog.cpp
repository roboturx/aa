#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase ("QSQLITE");
    db.setDatabaseName ("../db.db");
    if (!db.open ())
    {
        qDebug() << "veritabanı açılamadı";

    }
    qDebug() << "veritabanı açıldı";

    model = new QSqlQueryModel();
    model->setQuery ("SELECT * FROM tb_addr");

    ui->tableView->setModel (model);










}

Dialog::~Dialog()
{
    delete ui;
}

