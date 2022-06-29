#include "hc_treemodel.h"
#include <QTableView>
#include "dbase.h"
#include <QTreeView>
#include <QGridLayout>


hC_TreeModel::hC_TreeModel()

{
    qDebug()<<"hCmodel" ;
    stdmodel = new QStandardItemModel;
    proxymodel = new QSortFilterProxyModel;

    QSqlQuery  query("SELECT parentCode, AcName, ActCod FROM dbtb_accounts "
                     "ORDER BY ActCod ASC ");

    Q_ASSERT(query.isActive());
    const QSqlRecord rec = query.record();
    while (query.next())
    {

        QString AcName = query.value(rec.indexOf("AcName")).toString();
        int parentCode = query.value(rec.indexOf("parentCode")).toInt();
        int ActCod = query.value(rec.indexOf("ActCod")).toInt();

        QStandardItem *it = new QStandardItem(AcName);

        it->setData(ActCod, RelationRoles::CodeRole);

        if(parentCode == 0)
        {
            stdmodel->invisibleRootItem()->appendRow(it);
    //        qDebug()<<"0- "<< AcName ;
        }
        else
        {
            QModelIndexList ixs = stdmodel->match(stdmodel->index(0, 0),
                                                  RelationRoles::CodeRole,
                                                  parentCode,
                                                  1,
                                                  Qt::MatchExactly| Qt::MatchRecursive);

            if(ixs.size() > 0){
                QStandardItem *parent = stdmodel->itemFromIndex(ixs.first());
                parent->appendRow(it);

            }
        }
    }

}



