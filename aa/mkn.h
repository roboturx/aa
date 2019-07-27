#ifndef hC_H
#define hC_H

#include "globals.h"
#include "mkn_cinsi.h"
#include "mkn_marka.h"
#include "mkn_modeli.h"

class SKGComboBox;
namespace nSMkn {
class hC_MKN;
}


class hC_MKN : public hC_tBcreator
{
    Q_OBJECT
public:
    explicit hC_MKN(hC_tBcreator *parent = nullptr );
    ~hC_MKN();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QString *MKNid{};
    QLineEdit *led_barkod{};
    QLineEdit *led_malzeme{};
    QLineEdit *led_mknKurumno{};
    QLineEdit *led_mknPlaka{};

    hC_Le *hClE_cins ;
    hC_Le *hClE_mark ;
    hC_Le *hClE_modl ;
    QSpinBox *spn_mknYil{};
    QComboBox *cbx_mknYkt;
    QComboBox *cbx_mknSurucu;
    QComboBox *cbx_mknBirim;
    QComboBox *cbx_mknByer;

    QLineEdit *led_mknSase{};
    QLineEdit *led_mknMotor{};
    QLineEdit *led_mknMtip{};
    QDateTimeEdit *clndr_mknSurucutar{} ;
    QTextEdit *ted_mknAcklm{};

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

signals:
    void sgnMkn (QString,QByteArray);
};

#endif // hC_H
