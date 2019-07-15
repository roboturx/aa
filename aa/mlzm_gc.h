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

    hC_MLZM     *mlzm         {} ;
    QString     *mlzmKod      {} ;
    QString     *mlzmBarkod   {} ;
    QString     *mlzmMalzeme  {} ;
    QString     *mlzmBirim    {} ;

    QWidget     *mlzmGcWdgt   {} ;

    QLineEdit   *lE_barkod    {} ;
    QLineEdit   *lE_malzeme   {} ;
    QLineEdit   *lE_tarih     {} ;
    QComboBox   *cbx_grscks   {} ;
    QLineEdit   *lE_miktar    {} ;
    QLineEdit   *lE_fiyat     {} ;
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
