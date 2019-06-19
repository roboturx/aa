#ifndef CW_FTR_H
#define CW_FTR_H


#include "globals.h"
#include "hc_.h"
#include "mkn.h"
#include "dbase.h"


namespace Ui {
class hC_FTR;
}

class hC_FTR : public QWidget
{
    Q_OBJECT

public:

    void    ftr_setup();
    QString ftr_VTd();
    void    ftr_model(QSqlRelationalTableModel * );



    hC_Tv             *FTRtview{};
    QSqlRelationalTableModel *FTRmodel{};
    QItemSelectionModel      *FTRselectionMdl{} ;
    QDataWidgetMapper        *FTRmapper{};

    QSqlRelationalTableModel *mdlFtr{};



    QWidget     *wdgt_rsm;
    QWidget     *wdgt_mapFTR{}    ;

    QGridLayout *LyG_FTR{}    ;
    QGridLayout *LyG_FTR_dty{};
    QHBoxLayout *wrsm_ly ;

    QGroupBox   *gB_map{}  ;
    QLabel      *lB_brkd{} ;
    QLabel      *lB_FTR{} ;
    QLabel      *lB_rsm{}  ;


    QLineEdit   *lE_faturano{}  ;
    hC_Le   *lE_firma{} ;
    QLineEdit   *lE_tarih{};
    QLineEdit   *lE_aciklama{};


    // depo detay

    void    ftrdet_setup();
    QString ftrdet_VTd();
    void    ftrdet_model(QSqlRelationalTableModel * );



    hC_Tv             *FTRDETtview{};
    QSqlRelationalTableModel *FTRDETmodel{} ;
    QItemSelectionModel      *FTRDETselectionMdl{} ;
    QDataWidgetMapper        *FTRDETmapper{} ;

    QWidget     *wdgt_mapFTR_dty{};

    QLabel      *lB_FTRdet{}  ;
    QLineEdit   *lE_mlzdetbarkod{}  ;
    QLineEdit   *lE_mlzm{} ;
    hC_Le       *lE_mlzdetmlzm{} ;
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

    void wd_FTR()        ; //depo ui devamı
    void setup_viewFtr() ;
    void setup_modelFtr();
    void setup_mapFtr()  ;
    void setup_kntrlFtr();

    void wd_FTRdet()        ;
    void setup_viewFtrDet() ;
    void setup_modelFtrDet();
    void setup_mapFtrDet()  ;
    void setup_kntrlFtrDet();

private slots:
    void slt_ftr_hesap();

protected:
    void showEvent(QShowEvent *);

public:
    explicit hC_FTR(QWidget *parent = nullptr);
    ~hC_FTR() ;

};

#endif // CW_FTR_H
