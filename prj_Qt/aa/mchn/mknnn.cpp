#include "mknnn.h"
//#include "globals.h"

//! [Set up widgets]
mknnn::mknnn(QWidget *parent)
    : QWidget(parent)
{

    tree = new QTreeView;

    QList<QString >x;
    x.append ("22");
    x.append ("33");
    x.append ("44");
    x.append ("55");


}
//! [Set up connections and layouts]

//! [Set up the main table]
void mknnn::setupModel()
{
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(nullptr, tr("Cannot open database"),
            tr("Unable to establish a database connection.\n"
               "This example needs SQLite support. Please read "
               "the Qt SQL driver documentation for information how "
               "to build it."), QMessageBox::Cancel);
        return;
    }

    QSqlQuery query;
    query.exec("create table person (id int primary key, "
               "name varchar(20), address varchar(200), typeid int)");
    query.exec("insert into person values(1, 'Alice', "
               "'<qt>123 Main Street<br/>Market Town</qt>', 101)");
    query.exec("insert into person values(2, 'Bob', "
               "'<qt>PO Box 32<br/>Mail Handling Service"
               "<br/>Service City</qt>', 102)");
    query.exec("insert into person values(3, 'Carol', "
               "'<qt>The Lighthouse<br/>Remote Island</qt>', 103)");
    query.exec("insert into person values(4, 'Donald', "
               "'<qt>47338 Park Avenue<br/>Big City</qt>', 101)");
    query.exec("insert into person values(5, 'Emma', "
               "'<qt>Research Station<br/>Base Camp<br/>"
               "Big Mountain</qt>', 103)");
//! [Set up the main table]

//! [Set up the address type table]
    query.exec("create table addresstype (id int, description varchar(20))");
    query.exec("insert into addresstype values(101, 'Home')");
    query.exec("insert into addresstype values(102, 'Work')");
    query.exec("insert into addresstype values(103, 'Other')");
*/
    model = new QSqlRelationalTableModel(this);
    model->setTable("dbtb_mkn");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //typeIndex = model->fieldIndex("typeid");
    //model->setRelation(typeIndex,
      //     QSqlRelation("addresstype", "id", "description"));
    //model->select();
    typeIndex = model->fieldIndex("mkn_surucu");
    model->setRelation(typeIndex,
           QSqlRelation("dbtb_clsn", "kod_pr", "soyad"));
    model->select();
}
//! [Set up the address type table]

//! [Slot for updating the buttons]
void mknnn::updateButtons(int row)
{
    previousButton->setEnabled(row > 0);
    nextButton->setEnabled(row < model->rowCount() - 1);
}
//! [Slot for updating the buttons]
