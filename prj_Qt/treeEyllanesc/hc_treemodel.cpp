#include "hc_treemodel.h"
#include <QTableView>
#include "dbase.h"
#include <QTreeView>
#include <QGridLayout>


hC_TreeModel::hC_TreeModel()

{
    //modelle();
    //    dBase db;
    //    db.openDb ();

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

//    QTreeView *soltrview =new QTreeView;
//    soltrview->setModel(stdmodel);
//    //w->setWindowTitle ("mainwind treemodel");
//    soltrview->expandAll();
//    soltrview->show();

}



