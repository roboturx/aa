#ifndef CW_FTR_H
#define CW_FTR_H


#include "globals.h"
#include "hc_tableview.h"
#include "cw_mkn.h"
#include "dbase.h"


namespace Ui {
class Cw_ftr;
}

class Cw_ftr : public QWidget
{
    Q_OBJECT

public:

    DBase *dbase{};
    void setup_fatura() ;
    QWidget *wdgt_rsm;
    QHBoxLayout *wrsm_ly ;

    HC_TableView      *FTRtview{};
    QSqlRelationalTableModel    *FTRmodel{};
    QSqlRelationalTableModel    *mdlFtr{};
    QItemSelectionModel *FTRselectionMdl{} ;
    QDataWidgetMapper *FTRmapper{};

    QWidget     *wdgt_mapFTR{}    ;

    QGridLayout *LyG_FTR{}    ;
    QGridLayout *LyG_FTR_dty{};

    QGroupBox   *gB_map{}  ;
    QLabel      *lB_brkd{} ;
    QLabel      *lB_FTR{} ;
    QLabel      *lB_rsm{}  ;


    QLineEdit   *lE_faturano{}  ;
    HC_LE   *lE_firma{} ;
    QLineEdit   *lE_tarih{};
    QLineEdit   *lE_aciklama{};


    // depo detay
    QWidget     *wdgt_mapFTR_dty{};
    HC_TableView      *FTRDETtview{};
    QItemSelectionModel *FTRDETselectionMdl{} ;
    QSqlRelationalTableModel    *FTRDETmodel{} ;
    QDataWidgetMapper *FTRDETmapper{} ;


    QLabel      *lB_FTRdet{}  ;

    QLineEdit   *lE_mlzdetbarkod{}  ;
    QLineEdit   *lE_mlzm{} ;
    HC_LE   *lE_mlzdetmlzm{} ;

    QLineEdit   *lE_mlzdetaciklama{}  ;
    QLineEdit   *lE_mlzdettarih{} ;
    QLineEdit   *lE_mlzdetgc{} ;
    QLineEdit   *lE_mlzdetgcno{} ;
    QLineEdit   *lE_mlzdetmiktar{}  ;
    QLineEdit   *lE_mlzdetbirim{}  ;
    QLineEdit   *lE_mlzdetfiyat{}   ;
    QLineEdit   *lE_mlzdetkdv{}  ;
    QLineEdit   *lE_ftrToplam;
    QLineEdit   *lE_ftrKdv;
    QLineEdit   *lE_ftrGenelToplam;



private:
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
    void slt_ftr_hesap();
    //void slt_mlz_pB_EKLE_clicked();

protected:
    void showEvent(QShowEvent *);

public:
    explicit Cw_ftr(QWidget *parent = nullptr);
    ~Cw_ftr() ;

};

#endif // CW_FTR_H
