#ifndef hC_IE_H
#define hC_IE_H

#include <globals.h>
#include "dragwidget.h"
#include "mkn.h"

namespace nSIe {
class hC_IE;
}

class hC_IE : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_IE(QWidget *parent=nullptr);
    ~hC_IE();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    DragWidget *dragger;
    hC_MKN *mkn;
    hC_Le* hClE_mkn;
    QLineEdit* lE_ieno;
    QDateTimeEdit* dE_geltar;
    QComboBox* cbX_durum;
    QDateTimeEdit* dE_girtar;
    QDateTimeEdit* dE_ciktar;
    hC_Le* hClE_yetkili1;
    hC_Le* hClE_yetkili2;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

        void isEmriYeni(QDataStream* dataStream);
        void isEmriListele();

public: signals:
    void sgnIsEmri (int);

};

#endif // hC_IE_H
