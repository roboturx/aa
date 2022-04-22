#include "mainwindow.h"
#include "dbase.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>

#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSqlDatabase>

enum RelationRoles{
    CodeRole = Qt::UserRole + 1000,
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    QString qStr = "";

    dBase* dbase = new dBase;

    qDebug() << "000----------------------------------";
    qDebug() << dbase->lastError().text();
    qDebug()<<"Dbdriver : "<<dbase->driverName();
    QStandardItemModel model;
    if (dbase->isValid())
    {
        qDebug() <<"100";
        dbase->open();
        qDebug() <<"200";
        if (dbase->isOpen())
        {
            qDebug() <<"300";
            QSqlQuery query2(*dbase);
            query2.prepare("SELECT GroupCode, AcName, ActCod from adm_ac");
            query2.exec();
            if ( query2.isActive())
            {
                qDebug() <<"400";
                //model->setQuery(query);
                qDebug() <<"query is active-----------------------";


                const QSqlRecord rec = query2.record();
                while (query2.next()) {
                    QString AcName = query2.value(rec.indexOf("AcName")).toString();
                    int GroupCode = query2.value(rec.indexOf("GroupCode")).toInt();
                    int ActCod = query2.value(rec.indexOf("ActCod")).toInt();
                    QStandardItem *it = new QStandardItem(AcName);
                    it->setData(ActCod, RelationRoles::CodeRole);
                    if(GroupCode == 0)
                        model.invisibleRootItem()->appendRow(it);
                    else{
                        QModelIndexList ixs = model.match(model.index(0, 0),
                                                          RelationRoles::CodeRole,
                                                          GroupCode,
                                                          1,
                                                          Qt::MatchExactly| Qt::MatchRecursive);
                        if(ixs.size() > 0){
                            QStandardItem *parent = model.itemFromIndex(ixs.first());
                            parent->appendRow(it);
                        }
                    }
                }


                dbase->close();
                qDebug() << "opened success\n";
            }
            else
            {
                qDebug() << "001 -----------------------------------------------------";
                qDebug() << "    query is not active：DB being occupied, close manually";
                qDebug() << dbase->lastError().text();
                qFatal("failed to connect.");
                dbase->lastError().text();
                qDebug()<<"Dbdriver : "<<dbase->driverName();
                dbase->close();
                dbase->removeDatabase(dbase->connectionName());
                qApp->exit(1) ;
                qDebug()<<"NOT SELECTED";

            }
        }
        else
        {
            qDebug() << "DB is not open";

        }
    }
    else
    {
        qDebug() << "002 ---------------------------------------------------";
        qDebug() << "    DB is not valid ";
        qDebug() << "    query is not active：DB being occupied, close manually";
        qDebug() << dbase->lastError().text();
        qFatal("       failed to connect.");
        qDebug()<<"       Dbdriver : "<<dbase->driverName();
        dbase->close();
        dbase->removeDatabase(dbase->connectionName());
        qApp->exit(1) ;
        qDebug()<<"       NOT SELECTED";

    }





    QTreeView w;
    w.setModel(&model);
    w.expandAll();
    w.show();
    // MainWindow w;
    //w.show();
    return a.exec();
}
