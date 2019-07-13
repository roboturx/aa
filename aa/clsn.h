#ifndef CW_CLSN_H
#define CW_CLSN_H

#include "globals.h"

//#include "hc_.h"
//#include "dbase.h"
//#include <QtWidgets>

namespace nSClsn
{
class hC_CLSN;
}

class hC_CLSN : public QWidget
{
    Q_OBJECT

public:

    explicit hC_CLSN(QWidget *parent = nullptr);
    ~hC_CLSN();

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

    QLineEdit   *lE_isim=nullptr    ;
    QLineEdit   *lE_soyad=nullptr   ;
    QLineEdit   *lE_tc=nullptr;
    QLineEdit   *lE_doyer{};
    QDateEdit   *dT_dotar{};
    QLineEdit   *lE_baba{};
    QLineEdit   *lE_bolum{}   ;
    QLineEdit   *lE_meslek{}   ;

    QLineEdit   *lE_gorev{}   ;
    QLineEdit   *lE_adres{}   ;
    QLineEdit   *lE_sehir{}   ;
    QLineEdit   *lE_tel_cep{} ;
    QLineEdit   *lE_tel_ev{}  ;
    QLineEdit   *lE_eposta{}  ;
    QLineEdit   *lE_username{};
    QLineEdit   *lE_password{};
    QLineEdit   *lE_yetki{}   ;


    void    clsn_setup () ;

private:
    void clsn_wdgt  () ;
    void clsn_ui    () ;
    void clsn_kntrl () ;

protected:
    void showEvent(QShowEvent *);

};

#endif // CW_PER_H
