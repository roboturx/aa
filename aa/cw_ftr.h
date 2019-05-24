#ifndef CW_FTR_H
#define CW_FTR_H

#include "globals.h"
#include "hc_tableview.h"
#include "cw_mkn.h"

namespace Ui {
class Cw_ftr;
}

class Cw_ftr : public QWidget
{
    Q_OBJECT

public:

    void setup_fatura() ;

    QString     *tableName ;
    QString     *indexField ;
    QStringList *fieldList;


    HC_TableView      *FTRtview;
    QSqlRelationalTableModel    *FTRmodel;
    QDataWidgetMapper *FTRmapper;

    QWidget     *wdgt_mapFTR    ;

    QGridLayout *LyG_FTR    ;
    QGridLayout *LyG_FTR_dty;

    QGroupBox   *gB_map  ;
   // QCheckBox   *cX_mkn;
    QLabel      *lB_brkd ;
    QLabel      *lB_FTR ;
    QLabel      *lB_rsm  ;

    QLineEdit   *lE_faturano  ;
    QLineEdit   *lE_firma ;
    QLineEdit   *lE_tarih;


    // depo detay
    QWidget     *wdgt_mapFTR_dty;
    HC_TableView      *FTRDETtview;
    QItemSelectionModel *tV_dp_selectionMdl ;
    QSqlTableModel    *mlzDETmodel ;
    QDataWidgetMapper *FTRDETmapper ;


    QLabel      *lB_FTRdet  ;

    QLineEdit   *lE_mlzdetbarkod  ;
    QLineEdit   *lE_mlzdetmlzm ;

    QLineEdit   *lE_mlzdetaciklama  ;
    QLineEdit   *lE_mlzdettarih ;
    QLineEdit   *lE_mlzdetgc ;
    QLineEdit   *lE_mlzdetgcno ;
    QLineEdit   *lE_mlzdetmiktar  ;
    QLineEdit   *lE_mlzdetbirim  ;
    QLineEdit   *lE_mlzdetfiyat   ;
    QLineEdit   *lE_mlzdetkdv  ;


private:

    // depo veritabanı

    //depo


    void setup_uiFtr() ;
    void wd_FTR()      ; //depo ui devamı
    void wd_FTRdet()   ;

    void setup_modelFtr()    ;
    void setup_modelFtrDet() ;

    void setup_viewFtr()    ;
    void setup_viewFtrDet() ;

    void setup_mapFtr()    ;
    void setup_mapFtrDet() ;




private slots:
    //depo

    void slt_dp_toFirst();
    void slt_dp_toPrevious();
    void slt_dp_toNext();
    void slt_dp_toLast();

    void slt_ftr_hesap();
    void slt_mlz_ara();

    void slt_ftr_pB_EKLE_clicked();
    void slt_dp_pB_Eklersm_clicked();
   // void slt_dp_cX_grs_clicked();
    void slt_ftr_pB_SIL_clicked();
 //   void slt_dp_cX_mkn();

    void slt_dp_updButtons(int row);
    void slt_ftr_tV_rowchanged(const QModelIndex &index );
    void slt_dp_resimGoster(QModelIndex);

    // depo detay
    void slt_mlz_pB_EKLE_clicked();
    void slt_dpd_pB_SIL_clicked();

    void slt_dpd_updButtons(int row);
    void slt_dpd_toFirst();
    void slt_dpd_toPrevious();
    void slt_dpd_toNext();
    void slt_dpd_toLast();

protected:
    void showEvent(QShowEvent *);

public:
    explicit Cw_ftr(QWidget *parent = nullptr);
    ~Cw_ftr();

private:

};

#endif // CW_FTR_H
