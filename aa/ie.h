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

    hC_Le* hClE_mkn;
    QLineEdit* lE_ieno;
    QDateTimeEdit* dE_geltar;
    QComboBox* cbX_durum;
    QDateTimeEdit* dE_girtar;
    QDateTimeEdit* dE_ciktar;
    hC_Le* hClE_yetkili1;
    hC_Le* hClE_yetkili2;

    void setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;

public: signals:
    void sgnIsEmri (int);

};

#endif // hC_IE_H
