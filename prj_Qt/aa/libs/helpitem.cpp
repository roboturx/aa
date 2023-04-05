#include "helpitem.h"

HelpItem::HelpItem(const QString &helpAd,
                   const QString &helpAcklm,
                   const int &helpKod,
                   const QString &DBFile,
                   HelpItem *parent)
    : f_ms_helpAd(helpAd),
    f_ms_helpAcklm(helpAcklm),
    f_mi_helpKod(helpKod),
    f_ms_DBFile(DBFile),
    o_parent(parent)
{
    //  qDebug()<<"    ::Xitem constrctr";
    if (parent)
        o_parent->addChild(this);
}

HelpItem* HelpItem::takeChild(int row)
{
    // qDebug()<<"    ::Xitem takeechild";
    HelpItem *item = lo_children.takeAt(row);
    Q_ASSERT(item);
    item->o_parent = 0;
    return item;
}



//    QString HelpItem::todaysTime() const
//    {
//        // qDebug()<<"    ::Xitem todaystime";
//        int minutes = minutesForTask(true);
//        return QString("%1:%2").arg(minutes / 60)
//            .arg(minutes % 60, 2, 10, QChar('0'));
//    }


//    QString HelpItem::totalTime() const
//    {
//        // qDebug()<<"    ::Xitem totaltime";
//        int minutes = minutesForTask(false);
//        return QString("%1:%2").arg(minutes / 60)
//            .arg(minutes % 60, 2, 10, QChar('0'));
//    }


//    int HelpItem::minutesForTask(bool onlyForToday) const
//    {
//        // qDebug()<<"    ::Xitem minutesfortask";
//        int minutes = 0;
//        QListIterator<QPair<QDateTime, QDateTime> > i(m_dateTimes);
//        while (i.hasNext()) {
//            const QPair<QDateTime, QDateTime> &dateTime = i.next();
//            if (onlyForToday &&
//                dateTime.first.date() != QDate::currentDate())
//                continue;
//            minutes += (dateTime.first.secsTo(dateTime.second) / 60);
//        }
//        foreach (HelpItem *child, lo_children)
//            minutes += child->minutesForTask(onlyForToday);
//        return minutes;
//    }


//    void HelpItem::incrementLastEndTime(int msec)
//    {
//        // qDebug()<<"    ::Xitem icrementlastendtime";
//        QDateTime &endTime = m_dateTimes.last().second;
//        endTime.setTime(endTime.time().addMSecs(msec));
//    }


