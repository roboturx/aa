#ifndef hC_IE_H
#define hC_IE_H

#include <globals.h>
#include "hc_.h"
#include "iedet.h"

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
    void iedet_ui();

    void ie_view() ;
    void ie_map()  ;
    void ie_kntrl();

public:
    hC_IEDET* iedet;

    hC_Le* lE_mkn;
    QLineEdit* lE_ieno;
    QLineEdit* lE_geltar;
    QComboBox* cbX_durum;
    QLineEdit* lE_girtar;
    QLineEdit* lE_ciktar;
    hC_Le* lE_yetkili1;
    hC_Le* lE_yetkili2;

public: signals:
    void sgn (QString);

};



#endif // hC_IE_H
