#ifndef HC_IEDET_H
#define HC_IEDET_H

#include <QWidget>

#include <globals.h>
#include "hc_.h"

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
    QSqlRelationalTableModel* IEDETmodel{};
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

public slots:
    void rowChanged_IEDET(QModelIndex IEDETindex);
    void clk_IEDETbosh();

private slots:

    void onmnIE_IEDETekle();
    void rightMenu_IEDET(QPoint pos);
    void IEDETekle();
    void sil_IEDET();



public:
    /// iedet variables

    QWidget *wdgt_IEdetekle{};
    QWidget *wdgt_TSekle{};
    QWidget *wdgt_SCekle{};

    QString *IEno{};
    QString *IE_idno{};
    QString *IEdetno{};
    QLineEdit *lE_IEdetno{} ;
    QLineEdit *lE_IEdetaciklama{} ;

    QComboBox *cbx_IEdettamiryeri{} ;
    QComboBox *cbx_IEdetkurumicdis{} ;      // dbtb_clsn

    QComboBox *cbx_IEdetdurum{} ;

    QDateTimeEdit *dE_IEdetgirtarihi{} ;
    QDateTimeEdit *dE_IEdetciktarihi{} ;

    QComboBox *cbx_IEdetyapyer{} ;

    QDateTimeEdit *dE_IEdettarih{};


};





#endif // HC_IEDET_H
