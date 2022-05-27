
#include "treesqlmodel.h"
#include "treesqlitem.h"

#include <QtWidgets>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>


//! [0]
TreeSqlModel::TreeSqlModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << tr("Account Name------------------------------------")
             << tr("Parent Code")
             << tr("Account Code");
    rootItem = new TreeSqlItem(rootData);
    setupModelDataSQL(rootItem);
}
//! [0]

//! [1]
TreeSqlModel::~TreeSqlModel()
{
    delete rootItem;
}
//! [1]


void TreeSqlModel::setupModelDataSQL(TreeSqlItem *parent)
{
    // ilk parentitem headerlar
    QList<TreeSqlItem *> list_parentItems;
    list_parentItems << parent;

    // ilk parentcode 0 olmalı
    QList<int> list_parentCodes;
    list_parentCodes << 0;

    QSqlQuery query("SELECT f_parentCode, "
                    "f_AccountCode, f_AccountName "
                    " FROM dbtb_accounts"
                    " ORDER BY f_accountname ");

    Q_ASSERT_X(query.isActive (),"dosya seçilemedi","setup");

    const QSqlRecord rec = query.record();

    while (query.next())
    {
        int intprnt_Code = query.value(rec.indexOf("f_parentCode")).toInt();

        QList<QVariant> columnData;
        columnData << query.value(rec.indexOf("f_AccountName")).toString()
                   << query.value(rec.indexOf("f_parentCode")).toString()
                   << query.value(rec.indexOf("f_AccountCode")).toString () ;


        if ( intprnt_Code > list_parentCodes.last())
        {
            if (list_parentItems.last()->childCount() > 0)
            {
                list_parentItems << list_parentItems.last()
                             ->child(list_parentItems.last()->childCount()-1);
                list_parentCodes << query.value(rec.indexOf("f_parentCode")).toInt() ;
            }
        } else {
            while (intprnt_Code < list_parentCodes.last() &&
                   list_parentItems.count() > 0)
            {
                list_parentItems.removeLast();
                list_parentCodes.removeLast();
            }
        }
        // yeni parent ı ekle
        TreeSqlItem *parent = list_parentItems.last();
        parent->insertChildren(parent->childCount(), 1
                               , rootItem->columnCount());
        // tree nin row unu oluştur
        // burada satır satır treeview dolduruluyor
        // her satıra columdata daki veriler  ekleniyor
        for (int column = 0;
             column < columnData.size();
             ++column)
        {
            // buradaki set data view için geçerli
            // SQL için burda işlem yapılmıyor
            parent->child(parent->childCount() - 1)
                ->setData(column, columnData[column]);
        }
    }
}




//! [2]
int TreeSqlModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}
//! [2]

QVariant TreeSqlModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeSqlItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeSqlModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
TreeSqlItem *TreeSqlModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeSqlItem *item = static_cast<TreeSqlItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant TreeSqlModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex TreeSqlModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    //! [5]

    //! [6]
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeSqlItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
//! [6]

bool TreeSqlModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeSqlModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeSqlModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeSqlItem *childItem = getItem(index);
    TreeSqlItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool TreeSqlModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeSqlModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int TreeSqlModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() > 0)
        return 0;

    const TreeSqlItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}
//! [8]
//


bool TreeSqlModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}







bool TreeSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeSqlItem *item = getItem(index);
    qDebug()  << "MDLsetdata " <<"index"<< index.row()<<"-"<<index.column()
             << "---value--item->data 2 --> "
             <<value.toString()
             <<item->data(2).toInt();

    //////////////////////////////////////
    QSqlQuery query;
    query.prepare("UPDATE dbtb_accounts SET f_accountname=:name "
                  "WHERE f_accountcode = :id ");

    query.bindValue(":name", value.toString() );
    query.bindValue(":id",item->data(2).toInt() );
    if (query.exec())
    {

        qDebug()  << "MDLsetdata " << "OK update executed "  << query.executedQuery();

    }
    else
    {
        qDebug() << "MDLsetdata "  << "update not executed "
                 << query.executedQuery()<< "\n"
                 << query.lastError().text();

    }
    ////////////////////////////////////
    qDebug() << "MDLsetdata "  << "item->data 0 " << item->data(0).toString() ;
    qDebug()  << "MDLsetdata " << "item->data 1 " << item->data(1).toString() ;
    qDebug()  << "MDLsetdata " << "item->data 2 " << item->data(2).toString() ;
    qDebug() << "MDLsetdata "  << "value3 "  << value.toString();


    ////////////////////////////////////////

    bool result = item->setData(index.column(), value);

    if (result)
    {
        qDebug() << "MDLsetdata "  << "data changed ---------------------------------------";
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    }
    else
    {
        qDebug()  << "MDLsetdata " << "data N O T changed ---------------------------------------";
    }
    return result;
}
