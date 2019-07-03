#ifndef hC_IE_H
#define hC_IE_H

#include <globals.h>
//#include "hc_.h"


namespace ns_IE {
class hC_IE;
}

class hC_IE : public QWidget
{
    Q_OBJECT

public:
    explicit hC_IE(QWidget *parent = nullptr);
    ~hC_IE();

    void    ie_setup();
    QString ie_VTd();
    void    ie_model(QSqlRelationalTableModel * );


    hC_Tv*                    IEtview;
    QSqlRelationalTableModel* IEmodel{};
    QItemSelectionModel*      IEselectionMdl;
    QDataWidgetMapper*        IEmapper;

    QLabel *lB_ie{};
    QLabel *lB_rsm{};

private:
    void ie_ui()   ;
    void iedet_show();

    void ie_view() ;
    void ie_map()  ;
    void ie_kntrl();

public:
    //hC_IEDET* iedet;

    hC_Le* hClE_mkn;
    QLineEdit* lE_ieno;
    QDateTimeEdit* dE_geltar;
    QComboBox* cbX_durum;
    QDateTimeEdit* dE_girtar;
    QDateTimeEdit* dE_ciktar;
    hC_Le* hClE_yetkili1;
    hC_Le* hClE_yetkili2;

public: signals:
    void sgn (int);

};



#endif // hC_IE_H
