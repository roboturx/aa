#include "hc_treemodel.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QStringList>


hC_TreeModel::hC_TreeModel(QObject *parent)
    : QAbstractItemModel(parent)

{
    qDebug() <<"--------------------- treemodel constructor";
    QList<QVariant> rootData;
    rootData << "Account " << "Accountnumber"<<"fffff";
    qDebug() <<"--------------------- treemodel -> Treeitem first rootitem";
    rootItem = new hC_TreeItem(rootData,0);
    qDebug() <<"--------------------- treemodel setup model data";


    setupModelData(rootItem);
}

QSqlQuery hC_TreeModel::reSelectAll(const QString qStr)
{
    QSqlQuery query;

    if (!query.exec (qStr)){
        qDebug () << "1 ???? << query" << query.lastError().text() ;}
    else { qDebug () << "1 query.rcount" << rowCount();  }
    return query;
}

void hC_TreeModel::setupModelData(hC_TreeItem *parent)
{
    QList<hC_TreeItem*> parents;
    parents << parent; /// ilk parent headerlar

    {

        QSqlQuery query=reSelectAll(QString(
                "SELECT knm_ad, knm_id FROM dbtb_knm"));

        int _konumAD = query.record().indexOf("knm_ad");
        int _konumID = query.record().indexOf("knm_id");

        while (query.next())
        {
            QString name = query.value(_konumAD).toString();
            int knmid = query.value(_konumID).toInt();
           // qDebug () << "name " << name;

            /// treeitemlar için pathı böl
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
                    QString qStr;
                    qStr =  "";
                    if(node == nodeString.count() - 1)
                    {
                        qStr += "SELECT count(*) "
                                "FROM dbtb_knm "
                                "WHERE knm_id= ";
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
                    QSqlQuery query2;
                    if (!query2.exec (qStr))
                        qDebug () << "query 2 HATA ????"
                                  <<query2.lastError().text();

                    if(query2.next())
                        nChild = query2.value(0).toInt();

                    columnData << nChild;

                    qDebug () <<"-------------------------------"
                              << "node:" << node<< "/"<< nodeString.count()
                              <<" tpath:"<< temppath
                              <<" CD1 nstr.at node:" <<nodeString.at(node)
                             << " fn lastidx:" << lastidx
                             <<" hash:"<< hash
                            << " CD2 nchild:" << nChild;


                    if(lastidx != -1)
                    {
                        parents.at(lastidx)->appendChild(
                                    new hC_TreeItem(columnData, hash, parents.at(lastidx)));
                        parents <<  parents.at(lastidx)->child(
                                        parents.at(lastidx)->childCount()-1);
                        qDebug () <<" lastidx != -1"<< parents.at(lastidx)
                                    ->child(parents.at(lastidx)
                                            ->childCount()-1);
                        lastidx = -1;
                    }
                    else
                    {
                        parents.last()->appendChild(new hC_TreeItem(
                                         columnData, hash, parents.last()));
                        parents <<  parents.last()->child(
                                        parents.last()->childCount()-1);
                        qDebug () <<"lastidx= -1"
                                 <<parents.last()
                                     ->child(parents.last()
                                             ->childCount()-1);
                    }
                    qDebug ()  <<"---------------------------------";


                }
            }

        }
        //////////////////////////////
        qDebug() << "----------- p.length " << parents.length();
        int i = 0;
        do
        {
            qDebug() << "parents - " << parents.at(i)->data(0).toString()
                     << " - "
                     << parents.at(i)->data(1).toString()
                     << " --- i="<< i << "--" <<(i < parents.length());
            i++;
        }
        while ( i < parents.length());

        ///////////////////////////////////////


    }
}





///////////////////////////////////////////////////////////////////////////
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

    if (role != Qt::DisplayRole && role != Qt::EditRole)  /// editable
        return QVariant();

    hC_TreeItem *item = static_cast<hC_TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags hC_TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index); //editable
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
    // else
    return QModelIndex();
}

QModelIndex hC_TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    hC_TreeItem *childItem = static_cast<hC_TreeItem*>(index.internalPointer());
    hC_TreeItem *parentItem = childItem->parent();

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

/////////////// editables
bool hC_TreeModel::setData(const QModelIndex &index,
                           const QVariant &value,
                           int role)
{
    qDebug() <<"-***- treemodel VALUE "<< value
            <<" ROLE "<< role
           << " INDEX " << index.row() <<"-" << index.column() <<"- parent"
           << index.parent().row()<<"-"<< index.parent().column()  ;
    if (role != Qt::EditRole ||
            index.column() < 0 ||
            index.column() > 2 )
    {
        qDebug() << "editrole error";
        return false;
    }
    /////////////////////////
    /// \brief item
    ///
    hC_TreeItem *item1 = getItem(index);
    qDebug() <<" -*1*-  data 0: "<<item1->data(0).toString()
            << " data 1: "<< item1->data(1).toString()
            << " index " << index.row() <<"-" << index.column() <<"- parent"
            << index.parent().row()<<"-"<< index.parent().column() ;
    bool result = item1->setData(index.column(), value);
    // veriyi değiştir //////////////////////////////////////////////////

    hC_TreeItem *item2 = getItem(index);
    qDebug() << "result " << result <<" -*2*-  data 0: "<<item2->data(0).toString()
             << " data 1: "<< item2->data(1).toString()
             << " index " << index.row() <<"-" << index.column() <<"- parent"
             << index.parent().row()<<"-"<< index.parent().column() ;
    ////////////////////
    ///

    if (result)
    {
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        //  QModelIndex primaryKeyIndex = index.row(), 0);
        int id = data(index,Qt::EditRole).toInt();
        //   clear();

        bool ok=false;
        qDebug() << "index col " << index.column() ;
        if (index.column() == 0)
        {
            qDebug() << "setting firstname";
            ok = setFirstName(id, value.toString());

        }
        else
        {
            //     ok = setLastName(id, value.toString());
        }
        refresh();
    }
    return result;
}



void hC_TreeModel::refresh()
{
    QSqlQuery query;
    QString qStr/*, mesaj*/;
    qStr="SELECT * FROM dbtb_knm";
    if (!query.exec (qStr)){
        qDebug () << "1 ???? << query" << query.lastError().text() ;}
    else { qDebug () << "1 query.rcount" << rowCount();  }
    //  setQuery("select * from person");
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("xxxxxxxxxx"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));

}

//! [2]
bool hC_TreeModel::setFirstName(int id, const QString &firstName)
{
    QSqlQuery query;
    QString qStr=QString("UPDATE dbtb_knm "
                         "set knm_ad = '22222222222' "
                         "where knm_id = 2");
//            .arg(firstName)
            //.arg(id);
    query.prepare(qStr);
    if(query.exec())
    {
        qDebug() << "setted firstname"<< query.lastError().text() ;

        submit();
        return true;
    }
    else
    {
        qDebug() << "??????????? setting firstname"<< query.lastError().text() ;
        return false;

    }
    return true;
}

//! [2]

//bool hC_TreeModel::setLastName(int personId, const QString &lastName)
//{
//    QSqlQuery query;
//    query.prepare("update person set lastname = ? where id = ?");
//    query.addBindValue(lastName);
//    query.addBindValue(personId);
//    qDebug() <<"set lastname "<< personId <<" "<< lastName
//             << " "<< query.exec();

//    return query.exec();
//}











////////////////////////////////////////////////

bool hC_TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

hC_TreeItem *hC_TreeModel::getItem(const QModelIndex &index) const///
{
    if (index.isValid()) {
        hC_TreeItem *item = static_cast<hC_TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

////////////////////////////// editables

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


