
#include "taskitem.hpp"


TaskItem::TaskItem(const QString &hesapAd,
                   const bool topluHesap,
                   const QString &hesapTuru,
                   const QString &ustHesap,
                   TaskItem *parent)
        : m_hesapAd(hesapAd),
          m_topluHesap(topluHesap),
          m_parent(parent)
{
    if (m_parent)
        m_parent->addChild(this);
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
    foreach (TaskItem *child, m_children)
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
    TaskItem *item = m_children.takeAt(row);
    Q_ASSERT(item);
    item->m_parent = 0;
    return item;
}
