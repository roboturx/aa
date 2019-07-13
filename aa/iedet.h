#ifndef HC_IEDET_H
#define HC_IEDET_H

#include <globals.h>
#include "ie.h"

namespace nSIedet {
class hC_IEDET;
}

class hC_IEDET : public QWidget
{
    Q_OBJECT

public:

    explicit hC_IEDET(QWidget *parent = nullptr);
    ~hC_IEDET();

    ////////////////////////////////////////////////
    hC_Tv                    * tb_view    {} ;
    QItemSelectionModel      * tb_slctnMdl {} ;
    QSqlRelationalTableModel * tb_model    {} ;
    QDataWidgetMapper        * tb_mapper   {} ;


    QString                  * tb_name     {} ;
    hC_ArrD                  * tb_flds   {} ;
    QString                  * tb_ndex     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QWidget                  * win_Wdgt  {} ;
    QLabel                   * win_Label {} ;
    QLabel                   * win_Rsm   {} ;
/////////////////////////////////////////////////

    hC_IE* ie  {} ;
    int* ienoo {} ;

    QLineEdit *lE_IEno ;
    QLineEdit *lE_IEdetaciklama{} ;
    QComboBox *cbx_IEdettamiryeri{} ;
    QComboBox *cbx_IEdettamirbolum{} ;
    QComboBox *cbx_IEdetdurum{} ;
    QDateTimeEdit *dE_IEdetgirtarihi{} ;
    QDateTimeEdit *dE_IEdetciktarihi{} ;

    void setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;

    void clk_IEdetkaydet();
    void clk_IEdetdurum();
    void clk_IEdetclsn();
    void clk_IEdetyyer();


public:

};

#endif // HC_IEDET_H
