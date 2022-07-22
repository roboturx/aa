#ifndef CW_CLSN_H
#define CW_CLSN_H

#include "globals.h"

//#include "hc_.h"
//#include "dbase.h"
//#include <QtWidgets>

namespace nSClsn
{
class hC_CLSN;
}

class hC_CLSN : public hC_tBcreator
{
    Q_OBJECT
public:

    explicit hC_CLSN();
    ~hC_CLSN();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

     QLineEdit* lE_isim ;
     QLineEdit* lE_soyad;
     QLineEdit* lE_tc   ;
     QLineEdit* lE_doyer;
     QDateEdit* dT_dotar;
     QLineEdit* lE_baba;
     QLineEdit* lE_bolum;
     QLineEdit* lE_meslek;
     QLineEdit* lE_gorev;
     QLineEdit* lE_adres;
     QLineEdit* lE_sehir;
     QLineEdit* lE_tel_cep;
     QLineEdit* lE_tel_ev;
     QLineEdit* lE_eposta;
     QLineEdit* lE_username;
     QLineEdit* lE_password;
     QLineEdit* lE_yetki;
    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

protected:
    void showEvent(QShowEvent *);

};

#endif // CW_PER_H
