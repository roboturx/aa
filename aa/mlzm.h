#ifndef HC_MLZM_H
#define HC_MLZM_H


#include "globals.h"
#include "hc_.h"
#include "mkn.h"
#include "dbase.h"


namespace Ui {
class Cw_Mlzm;
class Kontrol;
}

class Cw_Mlzm : public QWidget
{   Q_OBJECT

public:

    DBase *dbase{} ;

    hC_Tv             *MLZMtview{};
    QSqlRelationalTableModel *MLZMmodel{};
    QItemSelectionModel      *MLZMselectionMdl{} ;
    QDataWidgetMapper        *MLZMmapper{};
    void setup_mlzm();


    QWidget     *wdgt_mapMlzm{}    ;
    QLabel      *lB_gt2{};
    QComboBox   *cbx_grs_tipi{};

    QGridLayout *LyG_Mlzm{}    ;
    QGridLayout *LyG_Mlzm_dty{};

    QGroupBox   *gB_map{}  ;
    QLabel      *lB_rsm;
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

    hC_Tv        *MLZMDETtview{};
    QItemSelectionModel *MLZMDETselectionMdl{} ;
    QSqlRelationalTableModel      *MLZMDETmodel{} ;
    QDataWidgetMapper   *MLZMDETmapper{} ;


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
    void setup_viewMlzm()    ;
    void setup_mapMlzm()    ;

    void setup_viewMlzmdet() ;
    void setup_modelMlzmdet() ;
    void setup_mapMlzmdet() ;

    void setup_kontrol();


private slots:

    //Mlzm

    void slt_Mlzm_hesap(QModelIndex Index);


protected:
    void showEvent(QShowEvent *);

signals:

    void sgnMalzeme (const QString sgnKod,
                     const QString sgnBarkod,
                     const QString sgnMalzeme,
                     const QString sgnBirim
                     ); //malzeme ismini yayınla



public:
    explicit Cw_Mlzm(QWidget *parent = nullptr);
    ~Cw_Mlzm();
};


#endif // HC_MLZM_H
