#include "hc_treemodel.h"
#include <QStringList>
#include <QtSql>
hC_TreeModel::hC_TreeModel(QObject *parent)
    : QAbstractItemModel(parent)

{
    QList<QVariant> rootData;
    rootData << "Nom" << "Nombre d'éléments";
    rootItem = new hC_TreeItem(rootData);
    setupModelData(rootItem);
}

hC_TreeModel::~hC_TreeModel()
{
    delete rootItem;
}

int hC_TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<hC_TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant hC_TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    hC_TreeItem *item = static_cast<hC_TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags hC_TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags; //0

    return QAbstractItemModel::flags(index);
}

QVariant hC_TreeModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex hC_TreeModel::index(int row, int column, const QModelIndex &parent)
    const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    hC_TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<hC_TreeItem*>(parent.internalPointer());

    hC_TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex hC_TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    hC_TreeItem *childItem = static_cast<hC_TreeItem*>(index.internalPointer());
    hC_TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int hC_TreeModel::rowCount(const QModelIndex &parent) const
{
    hC_TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<hC_TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int hC_TreeModel::findNode(unsigned int& hash, const QList<hC_TreeItem *> &tList)
{
    for(int idx = 0; idx < tList.size(); ++idx)
    {
        unsigned int z = tList.at(idx)->getIndex();
        if(z == hash)
            return idx;
    }

    return -1;
}



void hC_TreeModel::setupModelData(hC_TreeItem *parent)
{
    QList<hC_TreeItem*> parents;
    parents << parent;

    QString path = "my_db_path";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(db.open())
    {
        QSqlQuery query("SELECT path, id_file FROM file");
        int idPath = query.record().indexOf("path");
        int idIdx = query.record().indexOf("id_file");

        while (query.next())
        {
            QString name = query.value(idPath).toString();
            int id_file = query.value(idIdx).toInt();

            QStringList nodeString = name.split("\\", Qt::SkipEmptyParts);

            QString temppath = "";

            int lastidx = 0;
            for(int node = 0; node < nodeString.count(); ++node)
            {
                temppath += nodeString.at(node);
                if(node != nodeString.count() - 1)
                    temppath += "\\";

                unsigned int hash = qHash(temppath);
                QList<QVariant> columnData;

                columnData << nodeString.at(node);

                int idx = findNode(hash, parents);

                if(idx != -1)
                {
                    lastidx = idx;
                }
                else
                {
                    QString sQuery =  "";
                    if(node == nodeString.count() - 1)
                    {
                        sQuery += "SELECT count(*) FROM version WHERE id_file=";
                        sQuery += QString::number(id_file);
                        sQuery += ";";
                    }
                    else
                    {

                        sQuery += "SELECT count(*) FROM file WHERE path like '";
                        sQuery += temppath;
                        sQuery += "%';";
                    }


                    int nChild = 0;
                    QSqlQuery query2(sQuery);

                    if(query2.next())
                        nChild = query2.value(0).toInt();

                    columnData << nChild;

                    if(lastidx != -1)
                    {
                        parents.at(lastidx)->appendChild(new hC_TreeItem(columnData, parents.at(lastidx), hash));
                        parents <<  parents.at(lastidx)->child( parents.at(lastidx)->childCount()-1);
                        lastidx = -1;
                    }
                    else
                    {
                        parents.last()->appendChild(new hC_TreeItem(columnData, parents.last(), hash));
                        parents <<  parents.last()->child( parents.last()->childCount()-1);
                    }
                }
            }
        }
    }
}
