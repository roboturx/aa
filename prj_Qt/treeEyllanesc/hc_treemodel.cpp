#include "hc_treemodel.h"
#include <QTableView>
#include "dbase.h"
#include <QTreeView>
#include <QGridLayout>
#include <QSortFilterProxyModel>
//hC_TreeModel::hC_TreeModel(QObject *parent)
//    : QStandardItemModel{parent}
hC_TreeModel::hC_TreeModel()

{
    //modelle();
    dBase db;
    db.open ();

    stdmodel = new QStandardItemModel;
    QSqlQuery  query("SELECT GroupCode, AcName, ActCod from adm_ac "
                    "ORDER BY ActCod ASC ");

    if (query.isActive())
    {  qDebug()<<"q is active"; }
    else { qDebug()<<"q is NOT active"; }

    const QSqlRecord rec = query.record();

    while (query.next())
    {

        QString AcName = query.value(rec.indexOf("AcName")).toString();
        int GroupCode = query.value(rec.indexOf("GroupCode")).toInt();
        int ActCod = query.value(rec.indexOf("ActCod")).toInt();
        QStandardItem *it = new QStandardItem(AcName);
        it->setData(ActCod, RelationRoles::CodeRole);
        if(GroupCode == 0)
            stdmodel->invisibleRootItem()->appendRow(it);
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
            }
        }
        qDebug()<<"33333 "<< AcName <<" code role : "<< RelationRoles::CodeRole;
    }

    QSortFilterProxyModel proxymodel;
    // proxymodel.setSourceModel(treemodel);
    QTreeView *w =new QTreeView;

    w->setModel(stdmodel);
    w->setWindowTitle ("mainwind treemodel");
    // w->expandAll();
    QWidget *aa = new QWidget();

    QGridLayout aal(aa);
    aal.addWidget (w,0,0);
    // setCentralWidget (aa);
    aa->show ();
}

QStandardItemModel *hC_TreeModel::modelle()
{
//    dBase db;
//    db.open ();

//    stdmodel = new QStandardItemModel;
//    QSqlQuery  query("SELECT GroupCode, AcName, ActCod from adm_ac "
//                     "ORDER BY ActCod ASC ");

//    if (query.isActive())
//    {  qDebug()<<"q is active"; }
//    else { qDebug()<<"q is active"; }
//    qDebug()<<"11111111";
//    const QSqlRecord rec = query.record();

//    while (query.next())
//    {
// qDebug()<<"22222222";
//        QString AcName = query.value(rec.indexOf("AcName")).toString();
//        int GroupCode = query.value(rec.indexOf("GroupCode")).toInt();
//        int ActCod = query.value(rec.indexOf("ActCod")).toInt();
//        QStandardItem *it = new QStandardItem(AcName);
//        it->setData(ActCod, RelationRoles::CodeRole);
//        if(GroupCode == 0)
//            stdmodel->invisibleRootItem()->appendRow(it);
//        else
//        {
//            QModelIndexList ixs = stdmodel->match(stdmodel->index(0, 0),
//                                                  RelationRoles::CodeRole,
//                                                  GroupCode,
//                                                  1,
//                                                  Qt::MatchExactly| Qt::MatchRecursive);
//            if(ixs.size() > 0){
//                QStandardItem *parent = stdmodel->itemFromIndex(ixs.first());
//                parent->appendRow(it);
//            }
//        }
//            qDebug()<<"33333 "<< AcName <<" code role : "<< RelationRoles::CodeRole;
//    }

//    QSortFilterProxyModel proxymodel;
//    // proxymodel.setSourceModel(treemodel);
//    QTreeView *w =new QTreeView;

//    w->setModel(stdmodel);
//    w->setWindowTitle ("mainwind treemodel");
//   // w->expandAll();
//    QWidget *aa = new QWidget();

//    QGridLayout aal(aa);
//    aal.addWidget (w,0,0);
//   // setCentralWidget (aa);
//    aa->show ();

    return stdmodel;
}


