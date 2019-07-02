#ifndef HC_IEDET_H
#define HC_IEDET_H

#include <globals.h>
#include "hc_.h"
#include "ie.h"

namespace ns_IEDET {
class hC_IEDET;
}

class hC_IEDET : public QWidget
{
    Q_OBJECT

public:
    explicit hC_IEDET(QWidget *parent = nullptr);
    ~hC_IEDET();

public:

    void    iedet_setup();
    QString iedet_VTd();
    void    iedet_model(QSqlRelationalTableModel * );

    hC_Tv*                    IEDETtview;
    QSqlRelationalTableModel* IEDETmodel;
    QItemSelectionModel*      IEDETselectionMdl;
    QDataWidgetMapper*        IEDETmapper;

private:
    void iedet_ui()   ;
    void iedet_view() ;
    void iedet_map()  ;
    void iedet_kntrl();

    void clk_IEdetkaydet();
    void clk_IEdetdurum();
    void clk_IEdetclsn();
    void clk_IEdetyyer();


public:
    /// iedet variables

    hC_IE* ie ;
    int* ienoo;
    QLabel* lB_iedet ;
    QLabel* lB_rsm;

    QLineEdit *lE_IEno ;
    QLineEdit *lE_IEdetaciklama{} ;
    QComboBox *cbx_IEdettamiryeri{} ;
    QComboBox *cbx_IEdettamirbolum{} ;
    QComboBox *cbx_IEdetdurum{} ;
    QDateTimeEdit *dE_IEdetgirtarihi{} ;
    QDateTimeEdit *dE_IEdetciktarihi{} ;

};

#endif // HC_IEDET_H
