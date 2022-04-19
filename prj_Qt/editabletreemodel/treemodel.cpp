/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "treemodel.h"
#include "treeitem.h"

#include <QtWidgets>
#include <QtSql>
#include <QSqlQuery>


//! [0]
//TreeModel::TreeModel(const QStringList &headers, const QString &data, QObject *parent)
//: QAbstractItemModel(parent)
TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)

{
    QList<QVariant> rootData;

    //for (const QString &header : headers)///
    rootData << "header" << "headers number";

    rootItem = new TreeItem(rootData , 0);
    setupModelData(rootItem);
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}
//! [2]

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    //TreeItem *item = getItem(index);///
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    //return 0;//
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}




//! [5]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    //TreeItem *parentItem = getItem(parent);///
    TreeItem *parentItem ;
    //if (!parentItem)///
    //  return QModelIndex();///

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
//! [6]

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    //TreeItem *childItem = getItem(index);///
    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());

    //TreeItem *parentItem = childItem ? childItem->parent() : nullptr;///
    TreeItem *parentItem = childItem->parent();// parentItem();

    //  if (parentItem == rootItem || !parentItem())///
    if (parentItem == rootItem )
        return QModelIndex();

    //return createIndex(parentItem->childNumber(), 0, parentItem);///
    return createIndex(parentItem->row(), 0, parentItem);
}
//! [7]

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;//
    //const TreeItem *parentItem = getItem(parent);///
    //if (parent.isValid() && parent.column() > 0)///
    //  return 0;///
    if (parent.column() > 0)
        return 0;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());




    // return parentItem ? parentItem->childCount() : 0;///
    return parentItem->childCount() ;
}
//! [8]

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}


///
TreeItem *TreeModel::getItem(const QModelIndex &index) const///
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
///

int TreeModel::findNode(unsigned int& hash, const QList<TreeItem*>& tList)
{
    for(int idx = 0; idx < tList.size(); ++idx)
    {
        unsigned int z = tList.at(idx)->getIndex();
        if(z == hash)
            return idx;
    }

    return -1;
}


bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}


bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
void TreeModel::setupModelData(TreeItem *parent)
{
    QList<TreeItem *> parents;

    parents << parent;

    QString path = "my_db_path";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(db.open())
    {

        QSqlQuery query;
        QString qStr, mesaj;
        qStr = "CREATE TABLE IF NOT EXISTS dbtb_knm "
               "( knm_id INTEGER PRIMARY KEY ,"
               "  knm_ad TEXT"
               " )";
        if ( ! query.exec (qStr))
        {
            mesaj = "HATA - Konum Dosyası Oluştur u l a m a d ı . . .  "
                    "------------------------------------<br>"+
                    query.lastError().text() +
                    "------------------------------------";
        }
        else
        {/*
              qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\bbbb\\cccc') ";
              if (query.exec(qStr))
              {
                  qDebug () << "path added";
              }
              else
              {
                  qDebug () << "path NOT added " + query.lastError().text();
              }
              qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\xxxx\\cccc') ";
              if (query.exec(qStr))
              {
                  qDebug () << "path added";
              }
              else
              {
                  qDebug () << "path NOT added " + query.lastError().text();
              }
              qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\bbbb\\dddddddd') ";
              if (query.exec(qStr))
              {
                  qDebug () << "path added";
              }
              else
              {
                  qDebug () << "path NOT added " + query.lastError().text();
              }*/
        }



        qStr = "SELECT knm_ad, knm_id FROM dbtb_knm";
        if (query.exec(qStr))
        {
            qDebug () << "* records selected";
        }
        else
        {
            qDebug () << "* records NOT selected";
        }




        int i=0;
        while (query.next())
        {
            i++;

            int idPath = query.record().indexOf("knm_ad");
            int idIdx = query.record().indexOf("knm_id");

            QString name = query.value(idPath).toString();
            int id_knm = query.value(idIdx).toInt();

            QStringList nodeString = name.split("\\", Qt::SkipEmptyParts);

            QString str;
            foreach (str, nodeString)
            {
                qDebug() << "nodestring ----- " << str;
            }

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
                qDebug () << "ns.cnt : "
                          << node
                          <<  "/"
                           << nodeString.count()
                           << "  String "
                           << nodeString.at(node)
                           << " added to colmndata ------ hash"
                           << hash << "tpth " << temppath;

                // parents ın içinde node u bul
                int idx = findNode(hash, parents);

                if(idx != -1)
                {
                    lastidx = idx;
                }
                else
                {
                    qStr =  "";
                    if(node == nodeString.count() - 1)
                    {
                        //qStr += "SELECT count(*) FROM version WHERE id_file=";
                        qStr += "SELECT count(*) FROM dbtb_knm WHERE knm_id=";
                        qStr += QString::number(id_knm);
                        qStr += ";";
                        qDebug () << "son node işl3eniyor ............select ";
                    }
                    else
                    {

                        qStr += "SELECT count(*) FROM dbtb_knm WHERE knm_ad like '";
                        qStr += temppath;
                        qStr += "%';";
                        qDebug () << "* node işleniyoooorr ................ select";
                    }


                    int nChild = 0;
                    if (query.exec(qStr))
                    {
                        //qDebug () << "* select counted";
                    }
                    else
                    {
                        qDebug () << "* NOT select counted";
                    }


                    if(query.next())
                        nChild = query.value(0).toInt();

                    columnData << nChild;
                    qDebug () << "ns.cnt : "
                              << node
                              <<  "/"
                               << nodeString.count()
                               << "  nChild= "
                               << nChild
                               << " added to colmndata ------ hash"
                               << hash << "tpth " << temppath;

                    if(lastidx != -1)
                    {
                        parents.at(lastidx)->appendChild(
                                    new TreeItem(columnData, hash, parents.at(lastidx)));
                        // new TreeItem(columnData, hash));
                        parents <<  parents.at(lastidx)->child( parents.at(lastidx)->childCount()-1);
                        lastidx = -1;
                    }
                    else
                    {
                        parents.last()->appendChild(
                                    new TreeItem(columnData, hash, parents.last()));
                        //          new TreeItem(columnData, hash));
                        parents <<  parents.last()->child( parents.last()->childCount()-1);
                    }
                    QVariant x;
                    foreach (x, columnData)
                    {
                        qDebug() << "columndata ----- " << x;
                    }
                }
            }
        }
    }
}

/////////
///
/// orj file

//#include "restoretreemodel.h"
//#include <QStringList>
//#include <QtSql>


//RestoreTreeModel::RestoreTreeModel(QObject *parent)
//    : QAbstractItemModel(parent)
//{
//    QList<QVariant> rootData;
//    rootData << "Nom" << "Nombre d'éléments";
//    rootItem = new TreeItem(rootData);
//    setupModelData(rootItem);
//}

//RestoreTreeModel::~RestoreTreeModel()
//{
//    delete rootItem;
//}

//int RestoreTreeModel::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
//    else
//        return rootItem->columnCount();
//}

//QVariant RestoreTreeModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    if (role != Qt::DisplayRole)
//        return QVariant();

//    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

//    return item->data(index.column());
//}

//Qt::ItemFlags RestoreTreeModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return 0;

//    return QAbstractItemModel::flags(index);
//}

//QVariant RestoreTreeModel::headerData(int section, Qt::Orientation orientation,
//                                      int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->data(section);

//    return QVariant();
//}

//QModelIndex RestoreTreeModel::index(int row, int column, const QModelIndex &parent)
//const
//{
//    if (!hasIndex(row, column, parent))
//        return QModelIndex();

//    TreeItem *parentItem;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<TreeItem*>(parent.internalPointer());

//    TreeItem *childItem = parentItem->child(row);
//    if (childItem)
//        return createIndex(row, column, childItem);
//    else
//        return QModelIndex();
//}

//QModelIndex RestoreTreeModel::parent(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return QModelIndex();

//    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
//    TreeItem *parentItem = childItem->parentItem();

//    if (parentItem == rootItem)
//        return QModelIndex();

//    return createIndex(parentItem->row(), 0, parentItem);
//}

//int RestoreTreeModel::rowCount(const QModelIndex &parent) const
//{
//    TreeItem *parentItem;
//    if (parent.column() > 0)
//        return 0;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<TreeItem*>(parent.internalPointer());

//    return parentItem->childCount();
//}

//int RestoreTreeModel::findNode(unsigned int& hash, const QList<TreeItem*>& tList)
//{
//    for(int idx = 0; idx < tList.size(); ++idx)
//    {
//        unsigned int z = tList.at(idx)->getIndex();
//        if(z == hash)
//            return idx;
//    }

//    return -1;
//}



//void RestoreTreeModel::setupModelData(TreeItem *parent)
//{
//    QList<TreeItem*> parents;
//    parents << parent;

//    QString path = "my_db_path";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(path);
//    if(db.open())
//    {
//        QSqlQuery query("SELECT path, id_file FROM file");
//        int idPath = query.record().indexOf("path");
//        int idIdx = query.record().indexOf("id_file");

//        while (query.next())
//        {
//            QString name = query.value(idPath).toString();
//            int id_file = query.value(idIdx).toInt();

//            QStringList nodeString = name.split("\\", QString::SkipEmptyParts);

//            QString temppath = "";

//            int lastidx = 0;
//            for(int node = 0; node < nodeString.count(); ++node)
//            {
//                temppath += nodeString.at(node);
//                if(node != nodeString.count() - 1)
//                    temppath += "\\";

//                unsigned int hash = qHash(temppath);
//                QList<QVariant> columnData;

//                columnData << nodeString.at(node);

//                int idx = findNode(hash, parents);

//                if(idx != -1)
//                {
//                    lastidx = idx;
//                }
//                else
//                {
//                    QString sQuery =  "";
//                    if(node == nodeString.count() - 1)
//                    {
//                        sQuery += "SELECT count(*) FROM version WHERE id_file=";
//                        sQuery += QString::number(id_file);
//                        sQuery += ";";
//                    }
//                    else
//                    {

//                        sQuery += "SELECT count(*) FROM file WHERE path like '";
//                        sQuery += temppath;
//                        sQuery += "%';";
//                    }


//                    int nChild = 0;
//                    QSqlQuery query2(sQuery);

//                    if(query2.next())
//                        nChild = query2.value(0).toInt();

//                    columnData << nChild;

//                    if(lastidx != -1)
//                    {
//                        parents.at(lastidx)->appendChild(new TreeItem(columnData, parents.at(lastidx), hash));
//                        parents <<  parents.at(lastidx)->child( parents.at(lastidx)->childCount()-1);
//                        lastidx = -1;
//                    }
//                    else
//                    {
//                        parents.last()->appendChild(new TreeItem(columnData, parents.last(), hash));
//                        parents <<  parents.last()->child( parents.last()->childCount()-1);
//                    }
//                }
//            }
//        }
//    }
//}
