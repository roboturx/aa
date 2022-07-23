#ifndef TSNR_H
#define TSNR_H

#include "libs/globals.h"
//#include "hc_.h"


namespace nSTsnr {
class hC_TSNR;
}

class hC_TSNR : public  hC_tBcreator
{
   Q_OBJECT

public:
    explicit hC_TSNR();
    ~hC_TSNR();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QComboBox *cbx_TSmlzm{};
    QSqlTableModel *cbxTSmlzmModel{} ;

    QLineEdit *lE_TSno{};
    QDateTimeEdit *dE_TStarih{};
    QComboBox *cbx_TSmalzeme{};
    QLineEdit *lE_TSusta{};
    QLineEdit *lE_TSbfiyat{};
    QComboBox *cbx_TSdurum{};
    QLineEdit *lE_TSaciklama{};
    QString *TSdet_idno{};
    QString *TSdetno{};
    QString *TSno{};



    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

};

#endif // TSNR_H
