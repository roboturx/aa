#include "dbase.h"
#include <QSqlDatabase>
#include <QSqlError>

#include <QMessageBox>
#include <QSqlDriver>
#include <QSqlTableModel>

dBase::dBase()
{
    createConnection();
    addRecord ("ASSETS"                                       , 1, 0);
    addRecord ("FIXED ASSETS"                            , 101, 1 );
    addRecord ("TANGIBLE FIXED ASSETS"            , 10101, 101 );
    addRecord ("MACHINERY"               , 1010103, 10101 );
    addRecord ("LAND"                    , 1010101, 10101 );
    addRecord ("OFFICE EQUIPMENTS"       , 1010104, 10101 );
    addRecord ("MOTOR VEHICLES"          , 1010105, 10101 );
    addRecord ("INTANGIBLE FIXED ASSETS"          , 10102, 101 );
    addRecord ("COMPUTER SOFTWARE"       , 1010203, 10102 );
    addRecord ("GOODWILL"                , 10102001, 10102 );
    addRecord ("PATENTS & TRADE MARKS"   , 10102002, 10102 );
    addRecord ("ACC.DeP. FXD ASSETS"              , 10103, 101 );
    addRecord ("ACC.DP- MOTOR VHCLS"     , 10103004, 10103 );
    addRecord ("ACC.DP- OFF EQPMNTS"     , 10103003, 10103 );
    addRecord ("ACC.DP- MACHNRY"         , 10103001, 10103 );
    addRecord ("ACC.DP- COMPTRS"         , 10103002, 10103 );
    addRecord ("CURRENT ASSETS"                          , 102, 1 );
    addRecord ("dbtb_accounts RECEIVABLE"              , 10205, 102 );
    addRecord ("STOCK"                          , 1010105, 102 );
    addRecord ("DEPOSITS & PREPAYMENTS"           , 10212, 102 );
    addRecord ("LIABILITIES"                                  , 2, 0 );
    addRecord ("CAPITAL"                                      , 3, 0 );
    addRecord ("SALES"                                        , 4, 0 );
    addRecord ("EXPENSES"                                     , 5, 0 );
}



bool dBase::addRecord(QString  accNm, int accCd, int grpCd)
{
    // control the existence of the account name in the table




    //     QSqlQuery query;
    //        query.prepare("SELECT * FROM dbtb_accounts "
    //                      "WHERE AcName = '"+accNm+"'");
    //        //query.bindValue(0, "dbtb_accounts");
    //        //query.bindValue(1, accNm);


    //        if (! query.exec())
    //        {
    //            qDebug ()<< "  query is :: "<< query.executedQuery();
    //            qDebug ()<< " find query is not executed"<< query.lastError().text();
    //        }
    //    else
    //        {qDebug ()<< " find query is executed"<< query.executedQuery();}


    //        QString qryStr{};
    //qDebug ()<<qryStr;
    ////     QSqlQuery qery("SELECT * FROM dbtb_accounts where AcName = 'ASSETS'");
    ////         while (qery.next()) {
    ////             QString country = qery.value(0).toString();
    ////             qDebug()<<" --- " << country;

    ////         }





    ////    if (!query.isValid())
    ////    {
    ////        qDebug ()<< qryStr <<" find query is not activeted"<< query.lastError().text();
    ////        return false;
    ////    }

    //    if (!query.next())
    //    {
    //        qDebug ()<<" find query is not nexted"<< query.lastError().text();
    //        return false;
    //    }
    //    else
    //    {
    //        qDebug ()<<"nexted";
    //    }
    //    query.value(0).toString();
    //    qDebug ()<<"query reccount" << query.value(0).toString();
    //    if ( !query.isActive())
    //    {
    //        qDebug ()<<" find query is not active 2   " << query.lastError().text();
    //        return false;
    //    }
    //   // query.first()   ;
    //   // const QSqlRecord rec = query.record();


    QSqlQueryModel* MyItemModel = new QSqlQueryModel;
    //    model->setQuery(QString("SELECT specialite "
    //                            "as Spécialité, dci as DCI "
    //                            "FROM medocs"), db);


    MyItemModel->setQuery (QString(
            "SELECT * FROM dbtb_accounts WHERE AcName = '%1' ").arg(accNm) );

    qDebug ()<< " find query is executed";


  //  QTreeView *treeView = new QTreeView;
   // MyItemModel *sourceModel = new MyItemModel(this);
//    QSortFilterProxyModel *proxyModel =
//        new QSortFilterProxyModel();

//    proxyModel->setSourceModel(MyItemModel);
//    //treeView->setModel(proxyModel);
//    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

//    //    model->setQuery("SELECT AcName "
//    //                    "FROM dbtb_accounts  )");
//    proxyModel->setFilterKeyColumn(0); /// will filter by user name

//    proxyModel->setFilterRegularExpression(
//        QRegularExpression("AcName="+accNm,
//        QRegularExpression::CaseInsensitiveOption));




  //  proxyModel->select();

    //treeView->setModel(proxyModel);
  //  treeView->show();



    //QSqlTableModel model;
    /// model.setTable("dbtb_accounts");

    ///
    /// SET FILTER
    ///

    //   model.select();
    if ( MyItemModel->rowCount() > 0 )
    {
        qDebug ()<<"model rowcount > 0 :" << MyItemModel->rowCount() ;
        /// bu isimde ekayıt var
        /// UYARI YAP
        /// geri dön
        ///

        return false;
    }
    else
    {
        qDebug ()<<"model rowcount = 0 :"
                 << MyItemModel->rowCount() ;

        /// bu isimde kayıt yok yeni ekle
        ///
        /// ADD
        ///
        int row = 0;
        MyItemModel->insertRows(row, 1);
        MyItemModel->setData(MyItemModel->index(row, 0), accNm);
        MyItemModel->setData(MyItemModel->index(row, 1), accCd);
        MyItemModel->setData(MyItemModel->index(row, 2), grpCd);
        if (MyItemModel->submit())
        {
            qDebug()<<"Kayıt eklendi";
        }
        else
        {
            qDebug()<<"Kayıt eklen e m e d i " << ;
        }
    }


    //    if (query.value(0).toString() == accNm )
    //    {
    //        qDebug ()<<" record found :" << query.value(0).toString();
    //        return false;
    //    }
    //    else
    //        qDebug() <<"eklenemdi :"<<query.value(0).toString() << query.lastError().text();
    //    ///////// end of control


    //    // account not found, add it to the table
    //    QString str_accCd = QString::number(accCd);
    //    QString str_grpCd = QString::number(grpCd);


    //    qryStr = "insert into dbtb_accounts "
    //             "(AcName, ActCod, GroupCode) "
    //             "values ( \""
    //            +  accNm   + " \", " +
    //            str_accCd + ", "+
    //            str_grpCd + ") ";
    //    if(!query.exec(qryStr))
    //    {
    //        qDebug()<<query.lastError().text();
    //        return false;
    //    }
    //    else
    //    {
    //        qDebug() << "query executed "<<  accNm <<" record added . . .";
    //    }
    return true;
}



bool dBase::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "db.db"  );

    if (!db.open()) {
        qDebug()<<"Cannot open database\n"
                    "Unable to establish a database connection.\n"
                    "This example needs SQLite support. Please read "
                    "the Qt SQL driver documentation for information how "
                    "to build it.\n\n"
                    "Click Cancel to exit.";
        return false;
    }
    if ( ! db.tables().
         contains( "dbtb_accounts" ))
    {
        QSqlQuery query;
        if(!query.exec("CREATE TABLE IF NOT EXISTS dbtb_accounts "
                        " ( AcName TEXT,"
                        "ActCod INTEGER,"
                        "GroupCode INTEGER ) "))
            qDebug()<<query.lastError().text();
        qDebug() << "query executed table created . . .";
    }
    return true;
}


bool dBase::openDb()
{
    if (db.open() )
    {
        qDebug()<<  "dBase opened.";
        return true;

    }
    else
    {
        qDebug()<<  "dBase NOT opened.";
        return false;
    }
}
