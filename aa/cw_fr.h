﻿#ifndef CW_FR_H
#define CW_FR_H

#include "globals.h"

namespace Ui {
class Cw_fr;
}

class Cw_fr : public QWidget
{
    Q_OBJECT

public:
    explicit Cw_fr(QWidget *parent = nullptr);
    ~Cw_fr();

    QModelIndex *whichRow;
    QDataWidgetMapper *map_fr;
    QSqlTableModel *mdl_fr ;

    int         meslekIndex ;

    QComboBox   *cb_meslek  ;

    QGroupBox   *gB_map     ;

    QLabel      *lB_fr    ;
    QLabel      *lB_rsm    ;


    QLineEdit   *lE_unvan    ;
    QLineEdit   *lE_adres   ;
    QLineEdit   *lE_sehir;
    QLineEdit   *lE_vd;

    QLineEdit   *lE_vdno;
    QLineEdit   *lE_tel ;
    QLineEdit   *lE_eposta ;
    QLineEdit   *lE_yisim ;
    QLineEdit   *lE_ysoyad   ;
    QLineEdit   *lE_ytel ;

    QPushButton *pB_rsm     ;
    QPushButton *pB_ilk     ;
    QPushButton *pB_snrki   ;
    QPushButton *pB_oncki   ;
    QPushButton *pB_son     ;
    QPushButton *pB_ekle    ;
    QPushButton *pB_sil     ;

    QPushButton *pB_ara     ;
    QPushButton *pB_yaz     ;
    QPushButton *pB_kpt     ;

private:
    QTableView  *tV_fr     ;

    void setup_ui()        ;
    void setup_modelfr()  ;
    void setup_viewfr()   ;
    void setup_mapfr()   ;

private slots:
    void on_pB_KPT_clicked();
    void on_pB_ARA_clicked();
    void on_pB_YAZ_clicked();
    void on_pB_SIL_clicked();
    void on_pB_EKLE_clicked();
    void ontV_fr_resimGosterSLOT(QModelIndex);
    void onpB_fr_resimEklE_clickedSLOT();
    void r_toFirst();
    void r_toPrevious();
    void r_toNext();
    void r_toLast();

   // void resim(QModelIndex);
    void on_updateButtonsSLOT(int row);


protected:
    void showEvent(QShowEvent *);
};

#endif // CW_FR_H



