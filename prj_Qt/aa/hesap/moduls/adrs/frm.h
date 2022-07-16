#ifndef CW_FR_H
#define CW_FR_H

#include "globals.h"

namespace nSFrm {
class hC_FRM;
}

class hC_FRM : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_FRM();
    ~hC_FRM();

    hC_ArrD                  * tb_flds     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    int       meslekIndex{} ;
    QComboBox   *cb_meslek{};
    QGroupBox   *gB_map{}   ;
    QLabel      *lB_fr{}    ;

    QLineEdit   *lE_unvan{} ;
    QLineEdit   *lE_adres{} ;
    QLineEdit   *lE_sehir{} ;
    QLineEdit   *lE_vd{}    ;
    QLineEdit   *lE_vdno{}  ;
    QLineEdit   *lE_tel{}   ;
    QLineEdit   *lE_eposta{};
    QLineEdit   *lE_yisim{} ;
    QLineEdit   *lE_ysoyad{};
    QLineEdit   *lE_ytel{}  ;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

signals:
    void sgnfirma (const QString sgnfirma); //firma ismini

protected:
    void showEvent(QShowEvent *);
};

#endif // CW_FR_H



