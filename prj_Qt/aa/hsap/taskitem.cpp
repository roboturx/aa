
#include "taskitem.h"


TaskItem::TaskItem(const QString &hesapAd,
                   const QString &hesapAcklm,
                   const bool topluHesap,
                   const QString &hesapTuru,
                   const QString &ustHesap,
                   const quint64 &hesapKod,
                   TaskItem *parent)
        : f_ms_hesapAd(hesapAd),
          f_ms_hesapAcklm(hesapAcklm),
          f_mb_topluHesap(topluHesap),
          f_ms_hesapTuru(hesapTuru),
          f_ms_ustHesap(ustHesap),
          f_mi_hesapKod(hesapKod),
          o_parent(parent)
{
    if (parent)
        o_parent->addChild(this);
}


QString TaskItem::todaysTime() const
{
    int minutes = minutesForTask(true);
    return QString("%1:%2").arg(minutes / 60)
                           .arg(minutes % 60, 2, 10, QChar('0'));
}


QString TaskItem::totalTime() const
{
    int minutes = minutesForTask(false);
    return QString("%1:%2").arg(minutes / 60)
                           .arg(minutes % 60, 2, 10, QChar('0'));
}


int TaskItem::minutesForTask(bool onlyForToday) const
{
    int minutes = 0;
    QListIterator<QPair<QDateTime, QDateTime> > i(m_dateTimes);
    while (i.hasNext()) {
        const QPair<QDateTime, QDateTime> &dateTime = i.next();
        if (onlyForToday &&
            dateTime.first.date() != QDate::currentDate())
            continue;
        minutes += (dateTime.first.secsTo(dateTime.second) / 60);
    }
    foreach (TaskItem *child, lo_children)
        minutes += child->minutesForTask(onlyForToday);
    return minutes;
}


void TaskItem::incrementLastEndTime(int msec)
{
    QDateTime &endTime = m_dateTimes.last().second;
    endTime.setTime(endTime.time().addMSecs(msec));
}


TaskItem* TaskItem::takeChild(int row)
{
    TaskItem *item = lo_children.takeAt(row);
    Q_ASSERT(item);
    item->o_parent = 0;
    return item;
}
