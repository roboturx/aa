#include "modelle.h"

#include <QBrush>
#include <QFont>
#include <QIcon>
#include <QTime>
#include <QTimer>

Modelle::Modelle(QObject *parent)
    : QAbstractTableModel(parent)
    , timer(new QTimer(this))
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout , this, &Modelle::timerHit);
    timer->start();

    count = 0;
}

void Modelle::timerHit()
{
    //we identify the top left cell
    QModelIndex topLeft = createIndex(0,2);
    //emit a signal to make the view reread identified data
    emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}



Modelle::~Modelle()
{
}

int Modelle::rowCount(const QModelIndex &parent) const
{
    return 5;
}

int Modelle::columnCount(const QModelIndex &parent) const
{
    return 5;
}

int Modelle::cc()
{
    return count++;
}



QVariant Modelle::data(const QModelIndex &index, int role) const
{
    int indexR = index.row();
    int indexC = index.column();
    //   QString ccc = QString::number(count ++);
    /// show what happens
    ///
    //crount = 0 ;
    qDebug () << QString (" R-C = %2-%3 - Role = %4").
                 arg(indexR).arg(indexC).arg(role) ;


    switch (role)
    {
    case Qt::DisplayRole:
        // The key data to be rendered in the form of text. (QString)
        if (indexR == 1 && indexC == 1)
        {
            return QString("R = %1 - C = %2").arg(indexR).arg(indexC);
        }
        if ( indexR == 0 && indexC == 2)
        {
            return QTime::currentTime().toString();
        }
        //return QVariant();

    case Qt::FontRole:
        if (indexR == 0 && indexC == 0) { //change font only for cell(0,0)
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;
    case Qt::BackgroundRole:
        if (indexR == 1 && indexC == 2)  //change background only for cell(1,2)
            return QBrush(Qt::red);
        break;
    case Qt::TextAlignmentRole:
        if (indexR == 1 && indexC == 1) //change text alignment only for cell(1,1)
            return int(Qt::AlignRight | Qt::AlignVCenter);
        break;
    case Qt::CheckStateRole:
        if (indexR == 1 && indexC == 0) //add a checkbox to cell(1,0)
            return Qt::Checked;
        break;
    case Qt::DecorationRole:
        /// The data to be rendered as a decoration in the
        /// form of an icon. (QColor, QIcon or QPixmap)
        if (indexR == 0 && indexC == 4)
        {
            return QIcon(":/xx.png" );
        }
    case Qt::EditRole:
        /// The data in a form suitable for editing in an editor. (QString)
        break;

    case Qt::ToolTipRole:
        /// The data displayed in the item's tooltip. (QString)
        break;
    case Qt::StatusTipRole:
        /// The data displayed in the status bar. (QString)
        break;

    case Qt::WhatsThisRole:
        ///Qt::WhatsThisRole5The data displayed for the item in "What's This?" mode. (QString)
        break;
    case Qt::SizeHintRole:
        /// The size hint for the item that will be supplied to views. (QSize)
        break;
    }
    return "hC";
    //return QVariant();
}

QVariant Modelle::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("h first");
        case 1:
            return QString("h second");
        case 2:
            return QString("h third");
        }
    }
    if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        switch (section) {
        case 0:
            return QString("v first");
        case 1:
            return QString("v second");
        case 2:
            return QString("v third");
        }
    }
    return QVariant();
}


