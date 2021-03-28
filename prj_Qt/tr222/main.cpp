#include "mainwindow.h"
#include "hdatabase.h"
#include <QApplication>
#include <QtWidgets>
#include <QtSql>
#include <QTreeView>


static bool createConnection();

enum RelationRoles{
    CodeRole = Qt::UserRole + 1000,
};



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // Veritabanı
    HDataBase db;

    QStandardItemModel model;
    //QSqlQuery  query("SELECT Hsp_parentkod, Hsp_name, Hsp_kodu from Tb_Hsp");
    QSqlQuery query("SELECT Hsp_parentkod, Hsp_name, Hsp_kodu "
                                            "FROM Tb_Hsp "
                                            "ORDER BY Hsp_kodu ASC");
    const QSqlRecord rec = query.record();
    while (query.next()) {
        QString Hsp_name = query.value(rec.indexOf("Hsp_name")).toString();
        int Hsp_parentkod = query.value(rec.indexOf("Hsp_parentkod")).toInt();
        int Hsp_kodu = query.value(rec.indexOf("Hsp_kodu")).toInt();
        QStandardItem *it = new QStandardItem(Hsp_name);
        it->setData(Hsp_kodu, RelationRoles::CodeRole);
        if(Hsp_parentkod == 0)
        {

            model.invisibleRootItem()->appendRow(it);
        }
        else
        {
            QModelIndexList ixs = model.match(model.index(0, 0),
                                              RelationRoles::CodeRole,
                                              Hsp_parentkod,
                                              1,
                                              Qt::MatchExactly| Qt::MatchRecursive);
            if(ixs.size() > 0){
                QStandardItem *parent = model.itemFromIndex(ixs.first());
                parent->appendRow(it);
                parent->setIcon(QIcon(":/addons.png"));
            }
        }
    }
    QTreeView w;
    w.setAnimated(true);
    w.setHeaderHidden(true);
    w.setRootIsDecorated(true);
    /*if (ai_type == FolderItem)
        w.setIcon(QIcon(":/order.png"));
    else if (ai_type == PlaylistItem)
        setIcon(QIcon(":/images/playlist.png"));
    else if (ai_type == TrainingItem)
        setIcon(QIcon(":/images/training.png"));
    */

    w.setModel(&model);
    w.expandAll();
    w.show();
    return a.exec();
}



static bool createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        qDebug()<<"Cannot open database\n"
                  "Unable to establish a database connection.\n"
                  "This example needs SQLite support. Please read "
                  "the Qt SQL driver documentation for information how "
                  "to build it.\n\n"
                  "Click Cancel to exit.";
        return false;
    }
    QSqlQuery query;
    if(!query.exec("CREATE TABLE Tb_Hsp("
                    "h_snf INTEGER,"
                    "h_grp INTEGER,"
                    "h_dft INTEGER,"
                    "h_alt INTEGER,"
                    "h_kod TEXT,"
                    "h_name TEXT,"
                   "h_tipi TEXT,"
                   //alacak, borç, ç,ft bakiyeli
                   "h_cinsi"
                   // stok  - alış iade, satış, satış iade
                   // cari - kamu, özel
                   // gider - kasa - kdv
                   // kesinti -diğer - masraf merkezi
                   // erişim seviyesi
                    "h_parentkod INTEGER"
                    ")"))
        qDebug()<<query.lastError().text();
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                    "values(\"1 DÖNEN VARLIKLAR \", 1, 0)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"10 HAZIR DEĞERLER \", 10, 1)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                            "values(\"100 KASA \", 100, 10)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                            "values(\"101 ALINAN ÇEKLER \", 101, 10)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                            "values(\"102 BANKALAR \", 102, 10)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                            "values(\"103 VERİLEN ÇEK VE ÖDEME EMİRLERİ (-) \", 103, 10)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                            "values(\"108 DİĞER HAZIR DEĞERLER \", 108, 10)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"11 MENKUL KIYMETLER \", 11, 1)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"12 TİCARİ ALACAKLAR \", 12, 1)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"13 DİĞER ALACAKLAR \", 13, 1)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"15 STOKLAR \", 15, 1)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"17 YILLARA YAYGIN İNŞAAT VE ONARIM MALİYETLERİ \", 17, 1)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"18 GELECEK AYLARA AİT GİDERLER VE GELİR TAHAKKUKLARI \", 18, 1)");
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                        "values(\"19 DİĞER DÖNEN VARLIKLAR \", 19, 1)");


    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                    "values(\"2 DURAN VARLIKLAR\", 2, 0)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                    "values(\"3 KISA VADELİ YABANCI KAYNAKLAR\", 3, 0)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
                    "values(\"4 UZUN VADELİ YABANCI KAYNAKLAR\", 4, 0)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) values(\"5 ÖZ KAYNAKLAR\", 5, 0)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) values(\"6 GELİR TABLOSU HESAPLARI\", 6, 0)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) values(\"7 MALİYET HESAPLARI\", 7, 0)");

    query.exec("insert  into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) values(\"8 \", 8, 0)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) values(\"9 NAZIM HESAPLAR\", 9, 0)");

    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) values(\"0 \", 10, 0)");


       return true;
}

