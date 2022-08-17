#ifndef hC_HSPDTY_H
#define hC_HSPDTY_H

#include "libs/globals.h"
//#include "hc_hsp.h"


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

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QLineEdit   *lE_hspdtyID=nullptr    ;
    QLineEdit   *lE_hspID=nullptr    ;
    QDateEdit   *dE_tarih=nullptr   ;
    QLineEdit   *lE_no=nullptr    ;
    QLineEdit   *lE_aciklama{};
    QComboBox   *cB_transfer=nullptr;
    QLineEdit   *lE_r{};
    QLineEdit   *lE_borc{};
    QLineEdit   *lE_alacak{}   ;

    QGridLayout* win_Grid;
    int hspdtyID{};
    int hesapID{};
    QDate hspdtyTarih = QDate::currentDate();// fromString("1MM12car2003", "d'MM'MMcaryyyy");
    int reccount{};
    QModelIndex curIndex;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;
    void debugger(QString num) ;

protected:
    void showEvent(QShowEvent *);

private slots:
    void slt_tbx_rowChange(const QString sgnHspID, const QString sgnHspAd); //connect selectionmodel change
};

#endif // hC_HSPDTY_H
