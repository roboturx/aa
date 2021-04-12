/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "treeview.h"
#include "util.h"

#include <QGridLayout>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QTreeView>
#include <QMessageBox>
#include <QDebug>

#include <algorithm>

TreeView::TreeView()
    : QWidget()
{
    qDebug()<<" db  ";
    if (! this->createConnection() ) {
        QString msg = "** Create Database Error";
        throw msg;
        qDebug() <<msg;
    }

    setWindowTitle(tr("Tree View Model"));
    setMinimumSize(200, 350);

    QTreeView *treeView = new QTreeView();
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(4);
    qDebug()<<" model ";
    // get sql data
    QList<struCat> itemList;
    itemList = getData();
    qDebug()<<" getted data ";
    // sort the qlist data
    std::sort(itemList.begin(), itemList.end(), sortMe);

    // put qlist data in the tree
    QList<struCat>::iterator nK;

    QStandardItem *parentItem = model->invisibleRootItem();
    QStandardItem *lastParent = nullptr;
    //int ccount = 1;
    for (nK = itemList.begin(); nK != itemList.end(); ++nK) {

        QStandardItem *item = new QStandardItem;
        // item->setColumnCount(2);
        //   QStandardItem *item2 = new QStandardItem;
    //    model->setItem(ccount,0,item);
        // model->setItem(ccount,1,item2);
       // ccount++;
        item->setText(nK->catName);
        item->setFlags(Qt::ItemIsSelectable |
                       Qt::ItemIsEnabled |
                       Qt::ItemIsEditable );
        //    item2->setText(nK->catEkle);
        //  item2->setFlags(Qt::ItemIsSelectable |
        //        Qt::ItemIsEnabled |
        //   Qt::ItemIsEditable );

        if ( nK->catParent == 0 ) {
            parentItem->appendRow(item);
              //parentItem->appendRow(item2);

            // save this
            lastParent = item;

        }  else {
            lastParent->appendRow(item);
            //  lastParent->appendRow(item2);
        }

    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Food Categories"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("header added"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("gggggg"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("jjjjjjj"));
    model->sort(0);

    treeView->setModel(model);
    treeView->expandAll();

    //
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(treeView);
    setLayout(mainLayout);
}

bool TreeView::createConnection()
{
    static int counter = 100;
    QString treeName = "tree" + QString::number(counter++);


    m_db = QSqlDatabase::addDatabase("QSQLITE", treeName);
    m_db.setDatabaseName(":memory:");

    if (! m_db.open()) {
        QMessageBox::critical(nullptr, tr("Unable to Open Database"),
                              tr("Unable to establish a connection to the database.\n"
              "This example requires SQLite.\n\n"), QMessageBox::Cancel);
        return false;
    }
    else
        qDebug()<<"db qpened";

    QSqlQuery query(m_db);
    if (!query.exec("CREATE TABLE food "
                    "(catKey INTEGER PRIMARY KEY, "
                    "catName TEXT, "
                    "catParent INTEGER,"
                    "catEkle  TEXT)"  ))
    {
        query.lastError().text();
    }
    else
    {
        qDebug()<<"table created";
    }
    qbind(query,100 , "Demir Ali",0   ,"");
    qbind(query,101 , "Mustafa  ",100 ,"");
    qbind(query,102 , "hacı     ",101 ,"hacı");
    qbind(query,103 , "umut     ",102 ,"");
    qbind(query,104 , "yasemin  ",102 ,"");
    qbind(query,105 , "Kamil    ",0 ,"");
    qbind(query,106 , "hasibe   ",105 ,"");
    qbind(query,107 , "ayşe     ",106 ,"");
    qbind(query,108 , "şenay    ",107 ,"");
    qbind(query,109 , "deniz    ",108 ,"");
    qbind(query,110 , "ege      ",108 ,"");
    qbind(query,111 , "doğuş    ",0 ,"");
    return true;
}

void TreeView::qbind(QSqlQuery q, int key, QString kname, int parent, QString ekle)
{
    q.prepare("INSERT INTO food "
            "(catkey, catname, catparent, catekle) "
            "VALUES (:A,:B,:C,:D)");
    q.bindValue(":A", key);
    q.bindValue(":B", kname);
    q.bindValue(":C", parent);
    q.bindValue(":D", ekle);
    q.exec();

}


QList<TreeView::struCat> TreeView::getData()
{
    QSqlQuery query(m_db);
    //query.prepare("SELECT catKey, catName, catParent,catEkle FROM food");
    query.prepare("SELECT * FROM food");
    if (!query.exec()){
        qDebug() << query.lastError().text() ;
    }
    else
        qDebug()<<"exec";

    QList<struCat> itemList;
    struct struCat temp;
    int XXX=0;
    qDebug()<<XXX;
    while (query.next())  {
        temp.catKey    = query.value(0).toInt();
        temp.catName   = query.value(1).toString();
        temp.catParent = query.value(2).toInt();
        temp.catEkle   = query.value(3).toString();

        itemList.append(temp);
    }

    return itemList;
}

bool TreeView::sortMe(const TreeView::struCat &s1, const TreeView::struCat &s2)
{
    bool retVal = false;

    if ( s1.catParent == 0 && s2.catParent == 0)  {
        retVal = s1.catKey < s2.catKey;

    } else if ( s1.catParent == 0 && s2.catParent != 0 ) {

        if ( s1.catKey == s2.catParent ) {
            retVal = true;
        } else {
            retVal = s1.catKey < s2.catParent;
        }

    } else if ( s1.catParent != 0 && s2.catParent == 0 ) {

        if ( s1.catParent == s2.catKey ) {
            retVal = false;
        } else {
            retVal = s1.catParent < s2.catKey;
        }

    } else if ( s1.catParent != 0 && s2.catParent != 0 ) {
        retVal = s1.catParent < s2.catParent;
    }

    return retVal;

}


