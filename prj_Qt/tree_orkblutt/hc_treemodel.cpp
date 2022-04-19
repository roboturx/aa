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

        QSqlQuery query;
        QString qStr, mesaj;
        qStr = "CREATE TABLE IF NOT EXISTS dbtb_knm "
               "( knm_id INTEGER PRIMARY KEY ,"
               "  knm_ad TEXT"
               " )";
        if ( ! query.exec (qStr))
        {
            mesaj = "HATA - Konum Dosyası Oluştur u l a m a d ı . . .  "
                    "------------------------------------<br>"+
                    query.lastError().text() +
                    "------------------------------------";
        }
        else
        {
             qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\bbbb\\cccc') ";
          if (query.exec(qStr))
          {
              qDebug () << "knm_ad added";
          }
          else
          {
              qDebug () << "knm_ad NOT added " + query.lastError().text();
          }
          qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\xxxx\\cccc') ";
          if (query.exec(qStr))
          {
              qDebug () << "knm_ad added";
          }
          else
          {
              qDebug () << "knm_ad NOT added " + query.lastError().text();
          }
          qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\bbbb\\dddddddd') ";
          if (query.exec(qStr))
          {
              qDebug () << "knm_ad added";
          }
          else
          {
              qDebug () << "knm_ad NOT added " + query.lastError().text();
          }
        }



        qStr="SELECT knm_ad, knm_id FROM dbtb_knm";
        if (!query.exec (qStr))
            qDebug () << "1 ????";


        int idPath = query.record().indexOf("knm_ad");
        int idIdx = query.record().indexOf("knm_id");

        while (query.next())
        {
            QString name = query.value(idPath).toString();
            int knmid = query.value(idIdx).toInt();

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
                    qStr =  "";
                    if(node == nodeString.count() - 1)
                    {
                        //qStr += "SELECT count(*) FROM version WHERE knm_id=";
                        qStr += "SELECT count(*) FROM dbtb_knm WHERE knm_id=";
                        qStr += QString::number(knmid);
                        qStr += ";";
                    }
                    else
                    {

                        qStr += "SELECT count(*) FROM dbtb_knm WHERE knm_ad like '";
                        qStr += temppath;
                        qStr += "%';";
                    }


                    int nChild = 0;

                    if (!query.exec (qStr))
                        qDebug () << "2 ????";

                    if(query.next())
                        nChild = query.value(0).toInt();

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
