#include "proxymodel.h"
//const int InvalidHesapcode= -1;

ProxyModel::ProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)/*, currentHesapItem ()
*/{
  //  m_hesapCode = currentHesapItem->hesapKod ();
}


void ProxyModel::setHesapFiltre(TaskItem *currentHesap)
{
  if (m_hesapCode != currentHesap->hesapKod ())
        m_hesapCode = currentHesap->hesapKod ();
  invalidateFilter ();
}

void ProxyModel::clearFilters()
{
//    m_minimumZipcode = m_maximumZipcode = InvalidZipcode;
//    m_county.clear();
    m_hesapCode=5;
    invalidateFilter();
}


bool ProxyModel::filterAcceptsRow(int sourceRow,
                                  const QModelIndex &sourceParent) const
{
    QModelIndex indG = sourceModel()->index(sourceRow, 0, sourceParent);
    //QModelIndex indD = sourceModel()->index(sourceRow, 2, sourceParent);
    qDebug() <<"------------------------------";
    qDebug() <<"hscode-- "<< m_hesapCode;
    qDebug() <<"ingG---- "<< sourceModel()->data(indG).toUInt ();
    qDebug() <<"indD---- ";//<</* sourceModel()->data(indD).toUInt ()*/;

    if(sourceModel()->data(indG).toULongLong () != m_hesapCode)
        return false;
    return true;


}

QVariant ProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return sourceModel()->headerData(section, orientation,
                                     role);
}






