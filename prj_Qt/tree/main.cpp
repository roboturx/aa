


#include "mainwindow.h"
#include <QApplication>

#include <QMap>

#include <QTreeView>

#include <QStandardItem>
#include <QStandardItemModel>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

#include <QElapsedTimer>
#include <QDebug>
#include <QSqlError>

typedef enum
{
    FolderItem,
    PlaylistItem,
    TrainingItem

} ItemType;

class StandardItem : public QStandardItem
{
public:

    typedef enum
    {
        FolderItem,
        PlaylistItem,
        TrainingItem

    } ItemType;

    StandardItem(int ai_nodeId, int ai_nodeLevel, int ai_parentId, QString ai_nodeName, ItemType ai_type)
    {
        m_node_id = ai_nodeId;
        m_node_name = ai_nodeName;
        m_node_level = ai_nodeLevel;
        m_parent_id = ai_parentId;
        setText(m_node_name);
        if (ai_type == FolderItem)
            setIcon(QIcon(":/images/folder.png"));
        else if (ai_type == PlaylistItem)
            setIcon(QIcon(":/images/playlist.png"));
        else if (ai_type == TrainingItem)
            setIcon(QIcon(":/images/training.png"));
    }

    int m_node_id;
    QString m_node_name;
    int m_node_level;
    int m_parent_id;
};

typedef QMap<int, StandardItem*> MapStandardItem;

int main(int argc, char *argv[])
{




    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    QMap<int, MapStandardItem> map;

    QStandardItemModel * model = new QStandardItemModel();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("treee.db");
    if (!db.isOpen())
    {
        db.open();
        qWarning() << "veritabanı açıldı";
    }
    else
    {
        qWarning() << "veritabanı açılamadı";
    }






    QSqlQuery   q{};
    QString     ct, mesaj = "OK - Çalışan";
    QStringList inserts{};

    ct=   "CREATE TABLE IF NOT EXISTS FOLDERS ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "LEFT_RANGE INTEGER,"
            "RIGHT_RANGE INTEGER,"
            "_LEVEL_ INTEGER,"
            "NAME TEXT NOT NULL  )";




    if (!q.exec( ct ))
    {
        mesaj = "<br>HATA - FOLDERS Dosyası Oluşturulamadı  "
                        "<br>------------------------------------<br>"+
                q.lastError().text() +
                "<br>------------------------------------<br>";
    }
    else
    {
        mesaj = "OK - FOLDERS Dosyası YENİ Oluşturuldu ";


     inserts << "INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (0,  0, 0, "
                        "'1 DÖNEN VARLIKLAR')"
             << "INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE,"
                    "_LEVEL_,  NAME) VALUES (0,  0, 0, "
                        "'2 DURAN VARLIKLAR')"
             << " INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (0,  0, 0, "
                        "'3 KISA VADELİ YABANCI VARLIKLAR')"
             << " INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (4, 8, 0, "
                        "'4 UZUN VADELİ YABANCI VARLIKLAR')"
             << " INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (0,  0, 0, "
                        "'5 ÖZKAYNAKLAR')"
             << " INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (6,  2, 0, "
                        "'6 GELİR TABLOSU HESAPLARI')"
             << " INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (7,  5, 0, "
                        "'7 MALİYET HESAPLARI')"
             << " INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (8,  5, 0, "
                        "'8')"
             << " INSERT INTO FOLDERS (LEFT_RANGE, RIGHT_RANGE, "
                    "_LEVEL_,  NAME) VALUES (9,  5, 0, "
                        "'9 NAZIM HESAPLAR')"   ;









        foreach (QString qry , inserts)
        {
            if ( !q.exec(qry) )
            {
                mesaj = mesaj + "<br>İLK FOLDERS Eklenemdi"+
                        "<br>------------------------------------<br>"+
                        q.lastError().text ()+
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + "<br>İLK FOLDERS eklendi.";
            }
        } // foreach
    }

    qDebug ()<< mesaj;




    ct = "CREATE TABLE IF NOT EXISTS "
            "PLAYLISTS ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "FOLDER_ID INTEGER,"
            "NAME TEXT NOT NULL )";


    if (!q.exec( ct ))
    {
        mesaj = "<br>HATA - PLAYLISTS Dosyası Oluşturulamadı  "
                        "<br>------------------------------------<br>"+
                q.lastError().text() +
                "<br>------------------------------------<br>";
    }
    else
    {
        mesaj = "OK - PLAYLISTS Dosyası YENİ Oluşturuldu ";

        QStringList inserts2{};


        inserts2 << "INSERT INTO PLAYLISTS ( FOLDER_ID, NAME) VALUES (1, "
                        "'10 HAZIR DEĞERLER')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (1, "
                        "'11 MENKUL KIYMETLER')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (1, "
                        "'12 TİCARİ ALACAKLAR')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (2, "
                        "'20')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (2, "
                        "'21')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (2, "
                        "'22 TİCARI ALACAKLAR')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (2, "
                        "'23 DİĞER ALACAKLAR ')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (3, "
                        "'30 ')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (4, "
                        "'40')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (5, "
                        "'50')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (6, "
                        "'60 ')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (7, "
                        "'70 ')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (8, "
                        "'80 ')"
                << "INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (9, "
                        "'90 ')"



                    ;






        foreach (QString qry , inserts2)
        {
            if ( !q.exec(qry) )
            {
                mesaj = mesaj + "<br>İLK PLAYLISTS Eklenemdi"+
                        "<br>------------------------------------<br>"+
                        q.lastError().text ()+
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + "<br>İLK PLAYLISTS eklendi.";
            }
        } // foreach
    }

    qDebug ()<< mesaj;








    //    CREATE TABLE "PLAYLISTS" (
    //        "ID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    //        "FOLDER_ID" INTEGER,
    //        "NAME" TEXT NOT NULL
    //    );



    ct= "  CREATE TABLE IF NOT EXISTS TRAININGS ("
    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
    "FOLDER_ID INTEGER,"
    "NAME TEXT NOT NULL    )";



    if (!q.exec( ct ))
    {
        mesaj = "<br>HATA - TRAININGS Dosyası Oluşturulamadı  "
                        "<br>------------------------------------<br>"+
                q.lastError().text() +
                "<br>------------------------------------<br>";
    }
    else
    {
        mesaj = "OK - TRAININGS Dosyası YENİ Oluşturuldu ";



        foreach (QString qry , inserts)
        {
            if ( !q.exec(qry) )
            {
                mesaj = mesaj + "<br>İLK TRAININGS Eklenemdi"+
                        "<br>------------------------------------<br>"+
                        q.lastError().text ()+
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + "<br>İLK TRAININGS eklendi.";
            }
        } // foreach
    }





    // Filling of tables
 /*       for (int f=1; f <= 6; f++)
        {
            for (int p=1; p <= 2; p++)
                QSqlQuery(QString("INSERT INTO PLAYLISTS (FOLDER_ID, NAME) VALUES (%1, \"P%2\");").arg(f).arg(p));

            for (int t=1; t <= 3; t++)
                QSqlQuery(QString("INSERT INTO TRAININGS (FOLDER_ID, NAME) "
                                "VALUES (%1, \"T%2\");").arg(f).arg(t));
        }*/

    QElapsedTimer t;
    t.start();

    QSqlQuery query("SELECT parent.NAME as node_name, "
                            "parent._LEVEL_ as node_niv, "
                            "node.ID as node_id, "
     "(SELECT ID FROM FOLDERS "
            "WHERE LEFT_RANGE < node.LEFT_RANGE AND "
                    "RIGHT_RANGE > node.LEFT_RANGE "
                    "ORDER BY _LEVEL_ DESC LIMIT 1) as parent_id "
     "FROM FOLDERS AS node, FOLDERS AS parent "
     "WHERE node.LEFT_RANGE BETWEEN parent.LEFT_RANGE AND parent.RIGHT_RANGE "
     "GROUP BY node.NAME "
     "ORDER BY node.LEFT_RANGE ");

    while (query.next())
    {
        int node_niv = query.record().value("node_niv").toInt();
        int node_id = query.record().value("node_id").toInt();
        int parent_id = query.record().value("parent_id").toInt();
        QString node_name = query.record().value("node_name").toString();
        qWarning() <<"---------"<<  node_name;
        qWarning() << "niv      : "<< node_niv
                   << "parnt id :" << parent_id
                   << "node id  :"   << node_id;
        StandardItem * nodeItem = new StandardItem(node_id, node_niv, parent_id, node_name, StandardItem::FolderItem);

        // search for children playlists
        QSqlQuery q1(QString("SELECT * FROM PLAYLISTS WHERE FOLDER_ID = %1").arg(node_id));
        while (q1.next())
        {
            StandardItem * playlistItem = new StandardItem(q1.record().value("ID").toInt(),
                                                           node_niv + 1, node_id,
                                                           q1.record().value("NAME").toString(),
                                                           StandardItem::PlaylistItem);
            nodeItem->appendRow(playlistItem);
            qWarning() << playlistItem;
        }

        // search for children entrainements
        QSqlQuery q2(QString("SELECT * FROM TRAININGS "
                                "WHERE FOLDER_ID = %1").arg(node_id));
        while (q2.next())
        {
            StandardItem * trainingItem = new StandardItem(q2.record().value("ID").toInt(),
                                                           node_niv + 1, node_id,
                                                           q2.record().value("NAME").toString(),
                                                           StandardItem::TrainingItem);
            trainingItem->setText(q2.record().value("NAME").toString());
            nodeItem->appendRow(trainingItem);
            qWarning() <<  trainingItem;
        }

        // List of immediately higher level elements
        MapStandardItem list1 = map.value(node_niv - 1);

        if (!list1.isEmpty())
        {
            // If the parent exists, we associate
            // their child with him (this should always be the case!)
            StandardItem * parent = list1.value(parent_id);
            if (parent)
            {
                parent->appendRow(nodeItem);
            }

            // Adding the item to the list of same-level items
            MapStandardItem list2 = map.value(node_niv);
            list2.insert(nodeItem->m_node_id, nodeItem);
            map.insert(node_niv, list2);
        }
        else
        {
            // This element is the first in its level: it is added directly to the root
            model->appendRow(nodeItem);
            list1.insert(nodeItem->m_node_id, nodeItem);
            map.insert(node_niv, list1);
        }
    }

    qWarning() << "Loading time = " << t.elapsed() << "ms.";

    QTreeView * view = new QTreeView;
    view->setModel(model);
    view->setWindowTitle("treee");
    view->show();

    return a.exec();
}
