
#include <QtSql>

#include "mysqlmodel.h"

MySqlModel::MySqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    populate ();
}

//! [0]
Qt::ItemFlags MySqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
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
    if (index.column() < 1 || index.column() > 2)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt();

    clear();

    bool ok;
    if (index.column() == 1) {
        ok = setFirstName(id, value.toString());
    } else {
        ok = setLastName(id, value.toString());
    }
    refresh();
    return ok;
}
//! [1]

void MySqlModel::refresh()
{
    setQuery("select * from person");
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

void MySqlModel::populate()
{


    stdmodel = new QStandardItemModel;
    proxymodel = new QSortFilterProxyModel;

    QSqlQuery  query("SELECT GroupCode, AcName, ActCod FROM dbtb_accounts "
                    "ORDER BY ActCod ASC ");

    if (query.isActive())
    {  qDebug()<<"q is active"; }
    else { qDebug()<<"q is NOT active"; return; }

    const QSqlRecord rec = query.record();


    while (query.next())
    {

        QString AcName = query.value(rec.indexOf("AcName")).toString();
        int GroupCode = query.value(rec.indexOf("GroupCode")).toInt();
        int ActCod = query.value(rec.indexOf("ActCod")).toInt();

        //        QModelIndexList ccixs = stdmodel->match(stdmodel->index(0, 0),
        //                                              RelationRoles::CodeRole,
        //                                              AcName,
        //                                              1,
        //                                              Qt::MatchExactly| Qt::MatchRecursive);

        //        if(ccixs.size() > 0)
        //        {
        //            // account name finded
        //            qDebug()<<"account find";
        //            break;
        //        }



        QStandardItem *it = new QStandardItem(AcName);

        it->setData(ActCod, RelationRoles::CodeRole);

        if(GroupCode == 0)
        {
            stdmodel->invisibleRootItem()->appendRow(it);
            //        qDebug()<<"0- "<< AcName ;
        }
        else
        {
            QModelIndexList ixs = stdmodel->match(stdmodel->index(0, 0),
                                                  RelationRoles::CodeRole,
                                                  GroupCode,
                                                  1,
                                                  Qt::MatchExactly| Qt::MatchRecursive);

            if(ixs.size() > 0){
                QStandardItem *parent = stdmodel->itemFromIndex(ixs.first());
                parent->appendRow(it);
                //             qDebug()<<"1--- "<< AcName ;
            }
        }
    }

    //    QTreeView *soltrview =new QTreeView;
    //    soltrview->setModel(stdmodel);
    //    //w->setWindowTitle ("mainwind treemodel");
    //    soltrview->expandAll();
    //    soltrview->show();
}

//! [2]
bool MySqlModel::setFirstName(int personId, const QString &firstName)
{
    QSqlQuery query;
    query.prepare("update person set firstname = ? where id = ?");
    query.addBindValue(firstName);
    query.addBindValue(personId);
    return query.exec();
}
//! [2]

bool MySqlModel::setLastName(int personId, const QString &lastName)
{
    QSqlQuery query;
    query.prepare("update person set lastname = ? where id = ?");
    query.addBindValue(lastName);
    query.addBindValue(personId);
    return query.exec();
}
