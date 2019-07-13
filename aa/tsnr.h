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



    void    tsnr_setup();

private:
    void tsnr_wdgt  () ;
    void tsnr_ui    () ;
    void tsnr_kntrl () ;

};

#endif // TSNR_H
