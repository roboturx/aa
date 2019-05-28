#ifndef Cw_Mlzm_H
#define Cw_Mlzm_H

#include "globals.h"
#include "hc_tableview.h"
#include "cw_mkn.h"
#include "dbase.h"


namespace Ui {
class Cw_Mlzm;
}

class Cw_Mlzm : public QWidget
{   Q_OBJECT

public:

    DBase *dbase{} ;

    HC_TableView      *MLZMtview{};
    QDataWidgetMapper *MLZMmapper{};
    QSqlRelationalTableModel    *MLZMmodel{};
    void setup_mlzm();


    QWidget     *wdgt_mapMlzm{}    ;
    QLabel      *lB_gt2{};
    QComboBox   *cbx_grs_tipi{};

    QGridLayout *LyG_Mlzm{}    ;
    QGridLayout *LyG_Mlzm_dty{};

    QGroupBox   *gB_map{}  ;
    QLabel      *lB_brkd{} ;
    QLabel      *lB_Mlzm{} ;
    QLabel      *lB_mlzrsm{}  ;

    QLineEdit   *lE_barkod{}  ;
    QLineEdit   *lE_malzeme{} ;
    QLineEdit   *lE_aciklama{};
    QLineEdit   *lE_marka{}   ;
    QLineEdit   *lE_model{}   ;
    QLineEdit   *lE_cins{}    ;
    QComboBox   *cbx_birim{}   ;
    QLineEdit   *lE_giris{}   ;
    QLineEdit   *lE_cikis{}   ;
    QLineEdit   *lE_mevcut{}  ;




    // Mlzm detay
    QWidget     *wdgt_mapMlzm_dty{};
    HC_TableView      *MLZMDETtview{};
    QItemSelectionModel *tV_Mlzm_selectionMdl{} ;
    QSqlTableModel    *MLZMDETmodel{} ;
    QDataWidgetMapper *MLZMDETmapper{} ;


    QLabel      *lB_Mlzmdet{}  ;

    QLineEdit   *lE_d_barkod{}  ;
    QLineEdit   *lE_d_malzeme{} ;

    QLineEdit   *lE_d_tarih{}  ;
    QComboBox   *cbx_d_grs_cks{} ;
    QLineEdit   *lE_d_miktar{}  ;
    QLineEdit   *lE_d_fiyat{}   ;
    QLineEdit   *lE_d_aciklama{};



private:

    void setup_uiMlzm() ;
    void wd_Mlzm()      ; //Mlzm ui devamı
    void wd_Mlzmdet()   ;

    void setup_modelMlzm()    ;
    void setup_modelMlzmdet() ;

    void setup_viewMlzm()    ;
    void setup_viewMlzmdet() ;

    void setup_mapMlzm()    ;
    void setup_mapMlzmdet() ;




private slots:

    //Mlzm

  //  void slt_pB_ambar_grs_clicked();
  //  void slt_pB_ambar_cks_clicked();
  //  void cbx_grstipi_changed();




    void slt_Mlzm_toFirst();
    void slt_Mlzm_toPrevious();
    void slt_Mlzm_toNext();
    void slt_Mlzm_toLast();
    void slt_Mlzm_hesap();
    //void slt_Mlzm_hesap2();
    void slt_Mlzm_pB_EKLE_clicked();
    void slt_Mlzm_pB_Eklersm_clicked();
//    void slt_Mlzm_cX_grs_clicked();
    void slt_Mlzm_pB_SIL_clicked();
 //   void slt_Mlzm_cX_mkn();

    void slt_Mlzm_updButtons(int row);
    void slt_Mlzm_tV_rowchanged(const QModelIndex &index );
    void slt_Mlzm_resimGoster(QModelIndex);

    // Mlzm detay
    void slt_Mlzmd_pB_EKLE_clicked();
    void slt_Mlzmd_pB_SIL_clicked();

    void slt_Mlzmd_updButtons(int row);
    void slt_Mlzmd_toFirst();
    void slt_Mlzmd_toPrevious();
    void slt_Mlzmd_toNext();
    void slt_Mlzmd_toLast();

protected:
    void showEvent(QShowEvent *);

public:
    explicit Cw_Mlzm(QWidget *parent = nullptr);
    ~Cw_Mlzm();
};

#endif // Cw_Mlzm_H

