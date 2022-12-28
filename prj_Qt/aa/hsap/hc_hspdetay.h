#ifndef hC_HSPDTY_H
#define hC_HSPDTY_H

#include "libs/globals.h"
#include "libs/hc_.h"
#include "hc_hsp.h"
#include "cls_dlgt_combobox.h"
#include "hsap/proxymodel.h"
namespace nSHsp
{
class hC_HSPDTY;
}
class hC_HSPDTY : public hC_tBcreator
{
    Q_OBJECT
public:
    explicit hC_HSPDTY();
    ~hC_HSPDTY();

  //  QPair <quint64,QString> pair_Hesaplar;


    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    hC_hsp* win_hC_hsp;

    qint64  *SGNDhesapKod ;
    QString *SGNDhesapAd  ;

    QLineEdit   *lE_hspdtyID=nullptr    ;
    QLineEdit   *lE_hspID=nullptr    ;
    QDateEdit   *dE_tarih=nullptr   ;
    QLineEdit   *lE_no=nullptr    ;
    QLineEdit   *lE_aciklama{};
    QComboBox   *cB_transferHesap=nullptr;
    QLineEdit   *lE_r{};
    QLineEdit   *lE_borc{};
    QLineEdit   *lE_alacak{}   ;

    QGridLayout* win_Grid;
    int hspdtyID{};

    quint64* m_hesapID{};
    QString* m_hesapAd{};

    QDate hspdtyTarih = QDate::currentDate();// fromString("1MM12car2003", "d'MM'MMcaryyyy");
    int reccount{};
    QModelIndex curIndex;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;
    void debugger(QString num) ;

    ProxyModel *proxyModel;

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent*);

public slots:
    void slt_tbx_rowChange(quint64 *sgnHspID,
                           QString *sgnHspAd); //connect selectionmodel change
};

#endif // hC_HSPDTY_H
