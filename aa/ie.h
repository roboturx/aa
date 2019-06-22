#ifndef hC_IE_H
#define hC_IE_H

#include <globals.h>
#include "hc_.h"

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
    void ie_view() ;
    void ie_map()  ;
    void ie_kntrl();


};



#endif // hC_IE_H
