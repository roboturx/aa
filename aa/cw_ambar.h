#ifndef Cw_Ambar_H
#define Cw_Ambar_H

#include "globals.h"
#include "hc_tableview.h"
#include "cw_mkn.h"


namespace Ui {
class Cw_Ambar;
}

class Cw_Ambar : public QWidget
{   Q_OBJECT

public:

    HC_TableView      *AMBARtview;
    QSqlTableModel    *AMBARmodel;
    QDataWidgetMapper *AMBARmapper;

    QWidget     *wdgt_mapAmbar    ;
    QLabel      *lB_gt2;
    QComboBox   *cbx_grs_tipi;

    QGridLayout *LyG_Ambar    ;
    QGridLayout *LyG_Ambar_dty;

    QGroupBox   *gB_map  ;
    QLabel      *lB_brkd ;
    QLabel      *lB_Ambar ;
    QLabel      *lB_mlzrsm  ;

    QLineEdit   *lE_barkod  ;
    QLineEdit   *lE_malzeme ;
    QLineEdit   *lE_aciklama;
    QLineEdit   *lE_marka   ;
    QLineEdit   *lE_model   ;
    QLineEdit   *lE_cins    ;
    QComboBox   *cbx_birim   ;
    QLineEdit   *lE_giris   ;
    QLineEdit   *lE_cikis   ;
    QLineEdit   *lE_mevcut  ;




    // Ambar detay
    QWidget     *wdgt_mapAmbar_dty;
    HC_TableView      *AMBARDETtview;
    QItemSelectionModel *tV_Ambar_selectionMdl ;
    QSqlTableModel    *AMBARDETmodel ;
    QDataWidgetMapper *AMBARDETmapper ;


    QLabel      *lB_Ambardet  ;

    QLineEdit   *lE_d_barkod  ;
    QLineEdit   *lE_d_malzeme ;

    QLineEdit   *lE_d_tarih  ;
    QComboBox   *cbx_d_grs_cks ;
    QLineEdit   *lE_d_miktar  ;
    QLineEdit   *lE_d_fiyat   ;
    QLineEdit   *lE_d_aciklama;



private:

    void setup_uiAmbar() ;
    void wd_Ambar()      ; //Ambar ui devamı
    void wd_Ambardet()   ;

    void setup_modelAmbar()    ;
    void setup_modelAmbardet() ;

    void setup_viewAmbar()    ;
    void setup_viewAmbardet() ;

    void setup_mapAmbar()    ;
    void setup_mapAmbardet() ;




private slots:

    //Ambar

    void slt_pB_ambar_grs_clicked();
    void slt_pB_ambar_cks_clicked();
  //  void cbx_grstipi_changed();




    void slt_Ambar_toFirst();
    void slt_Ambar_toPrevious();
    void slt_Ambar_toNext();
    void slt_Ambar_toLast();
    void slt_Ambar_hesap();
    //void slt_Ambar_hesap2();
    void slt_Ambar_pB_EKLE_clicked();
    void slt_Ambar_pB_Eklersm_clicked();
    void slt_Ambar_cX_grs_clicked();
    void slt_Ambar_pB_SIL_clicked();
 //   void slt_Ambar_cX_mkn();

    void slt_Ambar_updButtons(int row);
    void slt_Ambar_tV_rowchanged(const QModelIndex &index );
    void slt_Ambar_resimGoster(QModelIndex);

    // Ambar detay
    void slt_Ambard_pB_EKLE_clicked();
    void slt_Ambard_pB_SIL_clicked();

    void slt_Ambard_updButtons(int row);
    void slt_Ambard_toFirst();
    void slt_Ambard_toPrevious();
    void slt_Ambard_toNext();
    void slt_Ambard_toLast();

protected:
    void showEvent(QShowEvent *);

public:
    explicit Cw_Ambar(QWidget *parent = nullptr);
    ~Cw_Ambar();
};

#endif // Cw_Ambar_H

