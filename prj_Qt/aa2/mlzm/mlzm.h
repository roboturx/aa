#ifndef HC_MLZM_H
#define HC_MLZM_H


#include "main/globals.h"

namespace nSMlzm {
class hC_MLZM;
}

class hC_MLZM : public hC_tBcreator
{   Q_OBJECT
public:
    explicit hC_MLZM();
    ~hC_MLZM();

    hC_ArrD                  * tb_flds     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QComboBox   *cbx_grs_tipi{} ;
    QLineEdit   *lE_barkod   {} ;
    QLabel      *lB_brkd     {} ;
    QLineEdit   *lE_malzeme  {} ;
    QLineEdit   *lE_aciklama {} ;
    QLineEdit   *lE_marka    {} ;
    QLineEdit   *lE_model    {} ;
    QLineEdit   *lE_cins     {} ;
    QComboBox   *cbx_birim   {} ;
    QLineEdit   *lE_giris    {} ;
    QLineEdit   *lE_cikis    {} ;
    QLineEdit   *lE_mevcut   {} ;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;


private slots:
    void slt_Mlzm_hesap(QModelIndex Index);

protected:
    void showEvent(QShowEvent *);

signals:
    void sgnMalzeme (int * sgnKod,
                     QString * sgnBarkod,
                     QString * sgnMalzeme,
                     QString * sgnBirim
                     ); //malzeme ismini yayınla


};

#endif // HC__H
