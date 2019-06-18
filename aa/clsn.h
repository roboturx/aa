﻿#ifndef CW_CLSN_H
#define CW_CLSN_H


#include "globals.h"
#include "hc_.h"
#include "dbase.h"


namespace ns_CLSN
{
class hC_CLSN;
}

class hC_CLSN : public QWidget
{   Q_OBJECT

public:

    explicit hC_CLSN(QWidget *parent = nullptr);
    ~hC_CLSN();

    void    clsn_setup();
    QString clsn_VT();
    void    clsn_model(QSqlRelationalTableModel * );

    QString* CLSNtableName {};

    DBase* dbase;
    hC_Tv*                    CLSNtview;
    QSqlRelationalTableModel* CLSNmodel;
    QItemSelectionModel*      CLSNselectionMdl;
    QDataWidgetMapper*        CLSNmapper;

    QLabel      *lB_clsn =nullptr    ;
    QLabel      *lB_rsm  =nullptr    ;





    QComboBox   *cb_meslek=nullptr  ;
    QGroupBox   *gB_map=nullptr     ;
      
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

private:
    void clsn_ui()   ;
    void clsn_view() ;
    void clsn_map()  ;
    void clsn_kntrl();

protected:
    void showEvent(QShowEvent *);


};

#endif // CW_PER_H