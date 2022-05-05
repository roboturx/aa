#include "myitemmodel.h"
#include "qtreeview.h"
#include <QSqlQuery>
#include <QSqlRecord>

MyItemModel::MyItemModel(QObject *parent)
    : QSqlQueryModel(parent) //QAbstractItemModel(parent)
{
    populate ();
}


void MyItemModel::populate()
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

//        QTreeView *soltrview =new QTreeView;
//        soltrview->setModel(stdmodel);
//        //w->setWindowTitle ("mainwind treemodel");
//        soltrview->expandAll();
//        soltrview->show();
}




QVariant MyItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

bool MyItemModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

QModelIndex MyItemModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex MyItemModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int MyItemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int MyItemModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

bool MyItemModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool MyItemModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void MyItemModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant MyItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    QVariant value = QSqlQueryModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return value.toString().prepend('#');
        else if (index.column() == 2)
            return value.toString().toUpper();
    }
  //  return QVariant();
}

bool MyItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        // FIXME: Implement me!

        if (index.column() < 1 || index.column() > 2)
            return false;

        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
        int id = data(primaryKeyIndex,Qt::EditRole).toInt();

        clear();

        bool ok=false;
        //    qDebug() <<"setdata "<< index.column() <<" "<< ok
        //             << " "<< value.toString()
        //             << " -id -"<< id
        //             <<"- index rowcol "<< index.row ()
        //             << "-"<< index.column ();

        if (index.column() == 1) {
            ok = setFirstName(id, value.toString());
        } else {
            ok = setLastName(id, value.toString());
        }
        refresh();

        emit dataChanged(index, index, QVector<int>() << role);
        return ok;
      //  return true;
    }
    return false;
}
///***
Qt::ItemFlags MyItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 1 || index.column() == 2)
        flags |= Qt::ItemIsEditable;
    return flags;

    //return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool MyItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool MyItemModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}

bool MyItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

bool MyItemModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}


void MyItemModel::refresh()
{
    setQuery("select * from person");
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

//! [2]
bool MyItemModel::setFirstName(int personId, const QString &firstName)
{
    QSqlQuery query;
    query.prepare("update person set firstname = ? where id = ?");
    query.addBindValue(firstName);
    query.addBindValue(personId);
    return query.exec();
}
//! [2]

bool MyItemModel::setLastName(int personId, const QString &lastName)
{
    QSqlQuery query;
    query.prepare("update person set lastname = ? where id = ?");
    query.addBindValue(lastName);
    query.addBindValue(personId);
    qDebug() <<"set lastname "<< personId <<" "<< lastName
             << " "<< query.exec();

    return query.exec();
}




