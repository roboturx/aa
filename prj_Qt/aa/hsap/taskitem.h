#ifndef TASKITEM_HPP
#define TASKITEM_HPP
/*
    Copyright (c) 2009-10 Qtrac Ltd. All rights reserved.

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QDateTime>
#include <QList>
#include <QPair>
#include <QString>


    // QList::value() returns default constructed value
    // for out of range
    // row
class TaskItem
{
public:
    explicit TaskItem(const quint64 &hesapKod,
                      const QString &hesapAd=QString(),
                      const bool bool_topluHesap=false,
                      const QString &hesapTuru=QString(),
                      const QString &ustHesap=QString(),
                      TaskItem *parent=0);
    ~TaskItem() { qDeleteAll(m_children); }

    QString hesapAd() const { return m_hesapAd; }
    void setHesapAd(const QString &hesapAd) { m_hesapAd = hesapAd; }
    quint64 hesapKod() const { return m_hesapKod; }
    void setHesapKod(const quint64 &hesapKod) { m_hesapKod = hesapKod; }

    bool isTopluHesap() const { return m_topluHesap; }
    void setTopluHesap(bool bool_topluHesap) { m_topluHesap = bool_topluHesap; }
    QString hesapTuru() const { return m_hesapTuru; }
    void setHesapTuru(const QString &hesapTuru) { m_hesapTuru = hesapTuru; }
    QString ustHesap() const { return m_ustHesap; }
    void setUstHesap(const QString &ustHesap) { m_ustHesap = ustHesap; }

    QList<QPair<QDateTime, QDateTime> > dateTimes() const
        { return m_dateTimes; }
    void addDateTime(const QDateTime &start, const QDateTime &end)
        { m_dateTimes << qMakePair(start, end); }
    QString todaysTime() const;
    QString totalTime() const;
    void incrementLastEndTime(int msec);
    TaskItem *parent() const { return m_parent; }
    TaskItem *childAt(int row) const { return m_children.value(row); }
    int rowOfChild(TaskItem *child) const
        { return m_children.indexOf(child); }
    int childCount() const { return m_children.count(); }
    bool hasChildren() const { return !m_children.isEmpty(); }
    QList<TaskItem*> children() const { return m_children; }

    void insertChild(int row, TaskItem *item)
        { item->m_parent = this; m_children.insert(row, item); }
    void addChild(TaskItem *item)
        { item->m_parent = this; m_children << item; }
    void swapChildren(int oldRow, int newRow)
//  qt6      { m_children.swap(oldRow, newRow); }
                    { m_children.swapItemsAt (oldRow, newRow); }
    TaskItem* takeChild(int row);

private:
    int minutesForTask(bool onlyForToday) const;

    quint64 m_hesapKod;
    QString m_hesapAd;
    bool m_topluHesap;
    QString m_hesapTuru;
    QString m_ustHesap;

    QList<QPair<QDateTime, QDateTime> > m_dateTimes;

    TaskItem *m_parent;
    QList<TaskItem*> m_children;
};

#endif // TASKITEM_HPP
