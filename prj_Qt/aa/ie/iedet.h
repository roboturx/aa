#ifndef HC_IEDET_H
#define HC_IEDET_H

#include "libs/globals.h"
#include "ie/ie.h"
//#include "dragwidget.h"

namespace nSIedet {
class hC_IEDET;
}

class hC_IEDET : public hC_tBcreator
{
    Q_OBJECT

public:

    explicit hC_IEDET(QWidget *parent=nullptr);
    ~hC_IEDET();


    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;
    //QString                  * tb_id    {};

  //  DragWidget *dbox;
    hC_IE* ie  {} ;
    int* ienoo {} ;

    QLineEdit *lE_IEno ;
    QLineEdit *lE_IEdetaciklama{} ;
    QComboBox *cbx_IEdettamiryeri{} ;
    QComboBox *cbx_IEdettamirbolum{} ;
    QComboBox *cbx_IEdetdurum{} ;
    QDateTimeEdit *dE_IEdetgirtarihi{} ;
    QDateTimeEdit *dE_IEdetciktarihi{} ;

    void tbsetup (int isEmriNo=-1) ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl (int ieno) ;

    void clk_IEdetkaydet();
    void clk_IEdetdurum();
    void clk_IEdetclsn();
    void clk_IEdetyyer();


public:

};

#endif // HC_IEDET_H
