
#include <QtSql>
#include <QTreeView>


#include "mysqlmodel.h"

MySqlModel::MySqlModel(QObject *parent)
    : QStandardItemModel/*QSqlQueryModel*/(parent)
{
    qDebug()<<"121212";
    populate ();
}

//! [0]
Qt::ItemFlags MySqlModel::flags(
    const QModelIndex &index) const
{
    // qDebug()<<"11 11 11";
    Qt::ItemFlags flags = QStandardItemModel/*QSqlQueryModel*/::flags(index);
    if (index.column() == 1 || index.column() == 2)
        flags |= Qt::ItemIsEditable;
    return flags;
}
//! [0]

//! [1]
bool MySqlModel::setData(const QModelIndex &index,
                         const QVariant &value,
                         int /* role */)
{
    qDebug()<<" index row-col" <<index.row()<<","<<index.column ();
    if (index.column() < 0 || index.column() > 2)
        return false;

    QModelIndex primaryKeyIndex =
        QStandardItemModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt();

    qDebug()<<"-*-*-*-*-*-*  setdatA";

    clear();

    bool ok;
    if (index.column() == 1)
    {
        ok = setFirstName(id, value.toString());
        qDebug()<<"-*-*-*-*-*-*  col == 1";
    }
    else
    {
        qDebug()<<"-*-*-*-*-*-*  col !== 1";
        ok = setLastName(id, value.toString());
    }
    refresh();
    return ok;
}
//! [1]

void MySqlModel::refresh()
{
    qDebug()<<"99999";
    populate ();
    //setQuery("select * from person");
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

void MySqlModel::populate()
{

    QSqlQuery  query("SELECT parentCode, AcName, ActCod FROM dbtb_accounts "
                    "ORDER BY ActCod ASC ");

    if (query.isActive())
    {  qDebug()<<"MySqlModel q is active"; }
    else { qDebug()<<"MySqlModel q is NOT active"; return; }

    const QSqlRecord rec = query.record();


    while (query.next())
    {
        QString AcName = query.value(rec.indexOf("AcName")).toString();
        int ActCod = query.value(rec.indexOf("ActCod")).toInt();
        int parentCode = query.value(rec.indexOf("parentCode")).toInt();

        QStandardItem *it =
            new QStandardItem(QString::number (parentCode)+" "+
                              QString::number (ActCod)+" "+
                              AcName);

        it->setData(ActCod, RelationRoles::CodeRole);

        if(parentCode == 0)
        {
            invisibleRootItem()->appendRow(it);
        }
        else
        {
            QModelIndexList ixs = match(index(0, 0),
                                        RelationRoles::CodeRole,
                                        parentCode,
                                        1,
                                        Qt::MatchExactly| Qt::MatchRecursive);

            if(ixs.size() > 0){
                QStandardItem *parent = itemFromIndex(ixs.first());
                parent->appendRow(it);

            }
        }
    }

}

//! [2]
bool MySqlModel::setFirstName(int personId, const QString &firstName)
{
    qDebug()<<"-*-*-*-*-*-*  setFname";
    QSqlQuery query;
    query.prepare("update dbtb_accounts set AcName = ? where ActCod = ?");
    query.addBindValue(firstName);
    query.addBindValue(personId);
    if (query.exec())
    {
        qDebug()<<"-*-*-*-*-*-*  setFname submit";
        submit ();
        return true;
    }
    return false;
}
//! [2]

bool MySqlModel::setLastName(int personId, const QString &lastName)
{
    qDebug()<<"-*-*-*-*-*-*  setLname"<<personId<<lastName;




    QSqlQuery query;

    // Your Code
    query.prepare("UPDATE dbtb_accounts SET "
                  "AcName=:name WHERE ActCod=:id");
    query.bindValue(":name", lastName);
    query.bindValue(":id", personId);
    if (query.exec())
        qDebug() << "Done OK";
    else
        qDebug() << "Huh!";

    // Dump the table id and ClientName
    query.exec("SELECT * FROM dbtb_accounts");
    while (query.next()) {
        qDebug() << "0="<<query.value(0).toString ()
                 << "1="<<query.value(1).toString ()
                 << "2="<< query.value(2).toString ();
    }

    return true;
    //    query.prepare("update dbtb_accounts set AcName = ? where ActCod = ?");
    //    query.addBindValue(lastName);
    //    query.addBindValue(personId);
    //    if (query.exec())
    //    {
    //        submit ();
    //        qDebug()<<"accname"<< query.value (0);
    //        qDebug()<<"accode"<<query.value (1);
    //        qDebug()<<"grpcd"<<query.value (1);
    //        qDebug()<<"-*-*-*-*-*-*  setLname submit";
    //        return true;
    //    }
    //    else
    //    {
    //        qDebug()<<query.lastError ().text ();
    //    return false;
    //    }
}
