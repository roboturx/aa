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
#include <QTreeView>
#include <QMessageBox>

#include <algorithm>

TreeView::TreeView()
   : QWidget()
{
   if (! this->createConnection() ) {
      QString msg = "** Create Database Error";
      throw msg;
      qDebug() <<msg;
   }

   setWindowTitle(tr("Tree View Model"));
   setMinimumSize(200, 350);

   QTreeView *treeView = new QTreeView();
   QStandardItemModel *model = new QStandardItemModel();
   model->setColumnCount(2);

   // get sql data
   QList<struCat> itemList;
   itemList = getData();

   // sort the qlist data
   std::sort(itemList.begin(), itemList.end(), sortMe);

   // put qlist data in the tree
   QList<struCat>::iterator nK;

   QStandardItem *parentItem = model->invisibleRootItem();
   QStandardItem *lastParent = nullptr;
    int ccount = 1;
   for (nK = itemList.begin(); nK != itemList.end(); ++nK) {

      QStandardItem *item = new QStandardItem;
     // item->setColumnCount(2);
      QStandardItem *item2 = new QStandardItem;
      model->setItem(ccount,0,item);
      model->setItem(ccount,1,item2);
      ccount++;
      item->setText(nK->catName);
      item->setFlags(Qt::ItemIsSelectable |
                     Qt::ItemIsEnabled |
                     Qt::ItemIsEditable );
      item2->setText(nK->catEkle);
      item2->setFlags(Qt::ItemIsSelectable |
                     Qt::ItemIsEnabled |
                     Qt::ItemIsEditable );

      if ( nK->catParent == 0 ) {
         parentItem->appendRow(item);
       //  parentItem->appendRow(item2);

         // save this
         lastParent = item;

       }  else {
         lastParent->appendRow(item);
         lastParent->appendRow(item2);
      }

   }

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Food Categories"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("header added"));
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

   QSqlQuery query(m_db);
   //query.exec("CREATE TABLE food (catKey int PRIMARY KEY, catName varchar(30), catParent int)");
   query.exec("CREATE TABLE food "
        "(catKey INT PRIMARY KEY, "
        "catName TEXT, "
        "catParent INT"
        "catEkle  TEXT)"  );

   query.exec("insert into food values(101, 'Salad',        0   ,'000101')");
   query.exec("insert into food values(102, 'Bread',        0   ,'000102')");
   query.exec("insert into food values(103, 'Cookies',      104 ,'104103')");
   query.exec("insert into food values(104, 'Dessert' ,     0   ,'000104')");
   query.exec("insert into food values(105, 'Vegetables',   0   ,'000105')");
   query.exec("insert into food values(106, 'Seafood',      0   ,'000106')");
   query.exec("insert into food values(107, 'Chicken',      0   ,'000107')");
   query.exec("insert into food values(108, 'Pastries',     104 ,'104108')");
   query.exec("insert into food values(109, 'Muffins',      102 ,'102109')");
   query.exec("insert into food values(110, 'Thanksgiving', 0   ,'000110')");
   query.exec("insert into food values(111, 'Pasta',        101 ,'101111')");
   query.exec("insert into food values(112, 'Greens',       101 ,'101112')");

   return true;
}

QList<TreeView::struCat> TreeView::getData()
{
   QSqlQuery query(m_db);
   query.prepare("SELECT catKey, catName, catParent,catEkle FROM food");
   query.exec();

   QList<struCat> itemList;
   struct struCat temp;

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


