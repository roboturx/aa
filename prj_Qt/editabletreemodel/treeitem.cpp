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

/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/
#include <QStringList>//
#include "treeitem.h"

//! [0]
//TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
  //  : itemData(data), parentItem(parent)

TreeItem::TreeItem(const QList<QVariant> &data, unsigned int id,
                       TreeItem *parent)
        : m_itemData(data), m_parentItem(parent)
{
    m_parentItem = parent;
        m_itemData = data;
        _id = id;

}
//! [0]

//! [1]
TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}
//! [1]

//! [2]
void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}
TreeItem *TreeItem::child(int number)
{
    if (number < 0 || number >= m_childItems.size())
        return nullptr;
    return m_childItems.at(number);
    //return m_childItems.value(row);//
}
//! [2]

//! [3]
int TreeItem::childCount() const
{
    return m_childItems.count();
}
//! [3]
//! [5]
int TreeItem::columnCount() const
{
    return m_itemData.count();
}
//! [5]
//! [4]
int TreeItem::childNumber() const///
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
    return 0;
}
//! [4]



//! [6]
QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
    //return m_itemData.value(column);
}
//! [6]
int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
//! [7]
bool TreeItem::insertChildren(int position, int count, int columns)///
{
    if (position < 0 || position > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QList<QVariant> data(columns);
        int new_id=0;///////////////////////////////////////////////////////////
        TreeItem *item = new TreeItem(data, new_id, this);
        m_childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool TreeItem::insertColumns(int position, int columns)///
{
    if (position < 0 || position > m_itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_itemData.insert(position, QVariant());

    for (TreeItem *child : qAsConst(m_childItems))
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
TreeItem *TreeItem::parent()///
{
    return m_parentItem;
}
//! [9]

//! [10]
bool TreeItem::removeChildren(int position, int count)///
{
    if (position < 0 || position + count > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_childItems.takeAt(position);

    return true;
}
//! [10]

bool TreeItem::removeColumns(int position, int columns)///
{
    if (position < 0 || position + columns > m_itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_itemData.remove(position);

    for (TreeItem *child : qAsConst(m_childItems))
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool TreeItem::setData(int column, const QVariant &value)///
{
    if (column < 0 || column >= m_itemData.size())
        return false;

    m_itemData[column] = value;
    return true;
}
//! [11]



//////
/// orj file


//#include <QStringList>

//#include "treeitem.h"

//TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent, unsigned int id)
//{
//    m_parentItem = parent;
//    m_itemData = data;
//    _id = id;
//}

//TreeItem::~TreeItem()
//{
//    qDeleteAll(m_childItems);
//}

//void TreeItem::appendChild(TreeItem *item)
//{
//    m_childItems.append(item);
//}

//TreeItem *TreeItem::child(int row)
//{
//    return m_childItems.value(row);
//}

//int TreeItem::childCount() const
//{
//    return m_childItems.count();
//}

//int TreeItem::columnCount() const
//{
//    return m_itemData.count();
//}

//QVariant TreeItem::data(int column) const
//{
//    return m_itemData.value(column);
//}

//TreeItem *TreeItem::parentItem()
//{
//    return m_parentItem;
//}

//int TreeItem::row() const
//{
//    if (m_parentItem)
//        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

//    return 0;
//}
