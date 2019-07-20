#ifndef HC_IEDET_H
#define HC_IEDET_H

#include <globals.h>
#include "ie.h"

namespace nSIedet {
class hC_IEDET;
}

class hC_IEDET : public hC_tBcreator
{
    Q_OBJECT

public:

    explicit hC_IEDET();
    ~hC_IEDET();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;
    //QString                  * tb_id    {};

    hC_IE* ie  {} ;
    int* ienoo {} ;

    QLineEdit *lE_IEno ;
    QLineEdit *lE_IEdetaciklama{} ;
    QComboBox *cbx_IEdettamiryeri{} ;
    QComboBox *cbx_IEdettamirbolum{} ;
    QComboBox *cbx_IEdetdurum{} ;
    QDateTimeEdit *dE_IEdetgirtarihi{} ;
    QDateTimeEdit *dE_IEdetciktarihi{} ;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

    void clk_IEdetkaydet();
    void clk_IEdetdurum();
    void clk_IEdetclsn();
    void clk_IEdetyyer();


public:

};

#endif // HC_IEDET_H
