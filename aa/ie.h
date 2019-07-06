#ifndef hC_IE_H
#define hC_IE_H

#include <globals.h>
//#include "hc_.h"


namespace nSIe {
class hC_IE;
}

class hC_IE : public QWidget
{
    Q_OBJECT

public:
    explicit hC_IE(QWidget *parent = nullptr);
    ~hC_IE();

    hC_Tv                    * IEtview    {} ;
    QSqlRelationalTableModel * IEmodel    {} ;
    QItemSelectionModel      * IEslctnMdl {} ;
    QDataWidgetMapper        * IEmapper   {} ;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel {} ;
    QLabel  * winRsm    {} ;


    hC_Le* hClE_mkn;
    QLineEdit* lE_ieno;
    QDateTimeEdit* dE_geltar;
    QComboBox* cbX_durum;
    QDateTimeEdit* dE_girtar;
    QDateTimeEdit* dE_ciktar;
    hC_Le* hClE_yetkili1;
    hC_Le* hClE_yetkili2;

    void    ie_setup () ;
    QString ie_VTd   () ;
    void    ie_model () ;

private:
    void ie_wdgt  () ;
    void ie_map   () ;
    void ie_ui    () ;
    void ie_view  () ;
    void ie_kntrl () ;

public: signals:
    void sgnIsEmri (int);

};

#endif // hC_IE_H
