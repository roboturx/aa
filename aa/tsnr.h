#ifndef TSNR_H
#define TSNR_H

#include <globals.h>
//#include "hc_.h"


namespace nSTsnr {
class hC_TSNR;
}

class hC_TSNR : public QWidget
{
    Q_OBJECT

public:
    explicit hC_TSNR(QWidget *parent = nullptr);
    ~hC_TSNR();

    hC_Tv                    * TSNRtview    {} ;
    QSqlRelationalTableModel * TSNRmodel    {} ;
    QItemSelectionModel      * TSNRslctnMdl {} ;
    QDataWidgetMapper        * TSNRmapper   {} ;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel {} ;
    QLabel  * winRsm   {} ;


    void    tsnr_setup();
    QString tsnr_VTd();
    void    tsnr_model();



private:
    void tsnr_wdgt  () ;
    void tsnr_map   () ;
    void tsnr_ui    () ;
    void tsnr_view  () ;
    void tsnr_kntrl () ;
public:


    QComboBox *cbx_TSmlzm{};
    QSqlTableModel *cbxTSmlzmModel{} ;

    QLineEdit *lE_TSno{};
    QDateTimeEdit *dE_TStarih{};
    QComboBox *cbx_TSmalzeme{};
    QLineEdit *lE_TSmiktar{};
    QComboBox *cbx_TSbirim{};
    QLineEdit *lE_TSbfiyat{};
    QComboBox *cbx_TSdurum{};
    QLineEdit *lE_TSaciklama{};
    QString *TSdet_idno{};
    QString *TSdetno{};
    QString *TSno{};






};




#endif // TSNR_H
