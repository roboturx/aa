#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>

Widget::Widget(QWidget *parent) : QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);




    qDebug()<<"cons";
    if (! initDatabase()) qDebug()<<"no database";
    qDebug() << "database";
    populateDataItem();
    qDebug()<<"connect";
    connect(ui->deleteButton, SIGNAL(clicked(bool)),this,
            SLOT(remove()));
    connect(ui->addButton, SIGNAL(clicked(bool)),this,
            SLOT(addnew()));
    connect(ui->submitButton, SIGNAL(clicked(bool)),this,
            SLOT(save()));
    qDebug()<<"connect";
}

void Widget::populateDataItem(){
    model=new QSqlTableModel(0, db);
    model->setTable("books");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Q_ASSERT(model->select());
    model->setHeaderData(0, Qt::Horizontal, tr("ISBN"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Edition"));
    model->setHeaderData(3, Qt::Horizontal, tr("Publisher"));
    model->setHeaderData(4, Qt::Horizontal, tr("Copyright"));
    model->setHeaderData(5, Qt::Horizontal, tr("Price"));
    model->setHeaderData(6, Qt::Horizontal, tr("Authors"));

    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);
}

bool Widget::initDatabase(){
    db=QSqlDatabase::addDatabase("QSQLITE","MyLibrary");

    db.setDatabaseName("test");

    return db.open();
}

void Widget::closeDatabase(){
    db.close();
}

Widget::~Widget()
{
    closeDatabase();
    delete model;
    delete ui;
}

void Widget::addnew(){
    int row=0;

    model->insertRows(row,1);
    model->setData(model->index(row,0),ui->edIsbn->text());
    model->setData(model->index(row,1),ui->edTitle->text());
    model->setData(model->index(row,2),ui->edEdition->text());
    model->setData(model->index(row,3),ui->edPublisher->text());
    model->setData(model->index(row,4),ui->edCopyright->text());
    model->setData(model->index(row,5),ui->dspinPrice->value());
    model->setData(model->index(row,6),ui->edAuthors->text());
}

void Widget::remove(){
    int row=ui->tableView->currentIndex().row();
    if(QMessageBox::question(0,"Delete", "Record no. "
                             +QString::number(row+1)
                             +" will be deleted. Are you sure?",
                             QMessageBox::No,QMessageBox::Yes)==
            QMessageBox::Yes){
        model->removeRow(row);
    }
}

void Widget::save(){
    bool flag=model->submitAll();
    if(flag==false)
        QMessageBox::critical(0,"Failed", "cannot save changes.");
    else
        QMessageBox::information(0,"success",
                                 "changes saved successfully.");
}
