#ifndef MLZM_GC_H
#define MLZM_GC_H


#include "globals.h"
#include "ftr.h"
#include "mlzm.h"
namespace nSMlzmGC {
class hC_tb_;
}

class hC_MLZMGC : public hC_tBcreator
{   Q_OBJECT

public:

    explicit hC_MLZMGC();
    ~hC_MLZMGC();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    hC_MLZM     *SGNmalzeme        {} ;

    int     *SGNEDmlzmKod      {} ;
    QString     *SGNEDmlzmBarkod   {} ;
    QString     *SGNEDmlzmMalzeme  {} ;
    QString     *SGNEDmlzmBirim    {} ;

    //QWidget     *mlzmGcWdgt   {} ;

    QLineEdit   *lE_kod       {} ;
    hC_Le       *hClE_barkod  {} ;
    hC_Le       *hClE_malzeme {} ;
    QLineEdit   *lE_tarih     {} ;
    QComboBox   *cbx_grscks   {} ;
    hC_Le       *hCle_gcno    {} ;
    QLineEdit   *lE_miktar    {} ;
    QComboBox   *cbx_birim    {} ;
    QLineEdit   *lE_fiyat     {} ;
    QSpinBox    *spn_kdv      {} ;
    QLineEdit   *lE_aciklama  {} ;


    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;


protected:
    void showEvent(QShowEvent *);


};

#endif // MLZM_GC_H
