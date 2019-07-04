#ifndef hC_MKN_H
#define hC_MKN_H

#include "globals.h"
//#include "hc_.h"
//#include "dbase.h"

//#include "clsn.h"
//#include "cw_grs.h"

//#include "dlgt_mkstok.h"
////#include "ftr_frmekle.h"

//#include "ie.h"
#include "mkn_cinsi.h"
#include "mkn_marka.h"
#include "mkn_modeli.h"
//#include "mkevrk.h"
//#include "tamamla.h"



class SKGComboBox;
namespace nSMkn {
class hC_MKN;
}


class hC_MKN : public QWidget
{
    Q_OBJECT
public:
    explicit hC_MKN(QWidget *parent = nullptr);
    ~hC_MKN();

    void    mkn_setup();
    QString mkn_VTd();
    void    mkn_model(QSqlRelationalTableModel * );

    //void set_mkn();


//    DBase *dbase;
    QLabel *lB_rsm;
    hC_Tv             *MKNtview ;
    QSqlRelationalTableModel *MKNmodel {} ;
    QItemSelectionModel      *MKNselectionMdl;
    QDataWidgetMapper        *MKNmapper {};

private:

    void set_uiMKN()   ;

    void set_viewMKN() ;
    void set_modelMKN();
    void set_mapMKN()  ;
    void set_kntrlMKN();

    void set_viewCNS() ;
    void set_modelCNS();
    void set_mapCNS()  ;
    void set_kntrlCNS();

    void set_viewMRK() ;
    void set_modelMRK();
    void set_mapMRK()  ;
    void set_kntrlMRK();

    void set_viewMDL() ;
    void set_modelMDL();
    void set_mapMDL()  ;
    void set_kntrlMDL();


public:
    void mkn_ui ();     // makina centralwidget

    void mkn_ui_tvs ();
    void mkn_ui_pbs ();
    void mkn_ui_tvmknmapper ();
    void mkn_ui_rsm ();
    void mkn_ui_tabw ();

    void mdll_mkn();
    void mdll_mkcins();
    void mdll_mkmark();
    void mdll_mkmodl();


    void MKNtview_view();   // mkn araç tableview
    void tV_cns_view();   // mkn cins tableview
    void tV_mrk_view();   // mkn marka tableview
    void tV_mdl_view();   // mkn model tableview

    void mkn_kontrol();
    void ss();


public slots:
    /// makina ikmal resmi değiştirilince
    void mknKurumno_ara();
private slots:

    //////////////////////////////////////////// tableview SLOTS



    void onmnMKN_yeniEklE_sgrtSLOT();
    void onmnMKN_yeniEklE_muaSLOT();
    void onmnMKN_yeniEklE_yagSLOT();
    void onmnMKN_yeniEklE_fltSLOT();
    void onmnMKN_yeniEklE_akuSLOT();
    void onmnMKN_yeniEklE_lstSLOT();
    void onmnMKN_yeniEklE_mknYktSLOT();
    void onmnMKN_yeniEklE_afzSLOT();
    void onmnMKN_yeniEklE_zcrSLOT();
    void onmnMKN_yeniEklE_hgsSLOT();


   // void onMKNtview_cmm_filterSLOT(QModelIndex Index);
   // void ww_mkcins();

public:

    // ui
    //QTableView *MKNtview{};
    QTableView *tV_mkcins{};
    QTableView *tV_mkmark{};
    QTableView *tV_mkmodl{};

    //QAction *act_to_ileri;
    //QAction *act_to_geri;

    QPushButton *pb_mkn{};
    QPushButton *pb_tab{};

    /// mkn variables
    // QString *processMKN;
    QString *MKNid{};
    QLineEdit *led_barkod{};
    QLineEdit *led_malzeme{};
    QLineEdit *led_mknKurumno{};
    QLineEdit *led_mknPlaka{};

//    QComboBox *cbx_mknCins{};
//    QSqlTableModel *cbxCinsiModel{};// dbtb_cins
//    QPushButton *pb_mknCins{};


//    QComboBox *cbx_mknMark{};
//    QSqlTableModel *cbxMarkaModel{};// dbtb_mknMarka
//    QPushButton *pb_mknMark{};
//    //void oncbx_mknMarkclickedSLOT();


//    QComboBox *cbx_mknModl{};
//    QSqlTableModel *cbxModeliModel{};// dbtb_model
//    QPushButton *pb_mknModl{};

    hC_Le *lE_cins ;
    hC_Le *lE_mark ;
    hC_Le *lE_modl ;
    QSpinBox *spn_mknYil{};

    QLineEdit *led_mknSase{};
    QLineEdit *led_mknMotor{};
    QLineEdit *led_mknMtip{};

    QPushButton *pb_mknYkt{};
    QComboBox *cbx_mknYkt{};       // dbtb_mknYkt
    void ykt();

    QPushButton *pb_mknSurucu{};
    QComboBox *cbx_mknSurucu{};       // dbtb_clsn
    QSqlTableModel *cbxClsnModel{};
    void src();

    QDateTimeEdit *clndr_mknSurucutar{} ;

    QPushButton *pb_mknBirim{};
    QComboBox *cbx_mknBirim{};
    void birim();              // dbtb_mknBirim

    QTextEdit *ted_mknAcklm{};

    QPushButton *pb_mknByer{};
    void byer();
    QComboBox *cbx_mknByer{};      // dbtb_mknByer




    // resim
    // rating




    /// yeni ioi no ekle
    //QWidget *yeniekle;


    /// ie variables

    QWidget *wdgt_IEekle{};
    QString *IEno{};
    QLineEdit *lE_IEno{} ;

    QDateTimeEdit *lE_IEtarih{} ;

    QComboBox *cbx_IEbolum{} ;    // dbtb_IEbolum
    QPushButton *pb_IEbolum{};

    QComboBox *cbx_IEusta{} ;      // dbtb_clsn

    QComboBox *cbx_IEdurum{} ;
    void clk_IEdurum();

    QComboBox *cbx_IEyetkili1{} ;
    void clk_IEclsn();
    QComboBox *cbx_IEyetkili2{} ;

    QDateTimeEdit *dE_IEgirtarihi{} ;
    QDateTimeEdit *dE_IEciktarihi{} ;

    QComboBox *cbx_IEyapyer{} ;
    void clk_IEyyer();
    QDateTimeEdit *dE_IEtarih{};

    //void IEekle();


 //   QDataWidgetMapper *MKNmapper{};


    void wd_mppr();
    QWidget *wdgt_mppr{};
    QWidget *wdgt_sol{};
    QWidget *wdgt_tv{};
    QWidget *wdgt_rsm{};

    QLabel *Wd_Rsm{};

    QPushButton *pb_rsmEkle{};
    QPushButton *pb_rsm{};





    QTabWidget *wtab{};

    //layouts
    QSplitter *qs{};
    //  QHBoxLayout *pbL;       // pushbuttons
    //   QGridLayout *tV_l;      // pbs , tv mkn
    //  QGridLayout *mapperL;   // mapper

    QWidget *wdgt_IE{};
    QWidget *wdgt_IEdet{};
    QWidget *wdgt_evrk{};
    QWidget *wdgt_bkm{} ;
    QWidget *wdgt_arz{};

    QToolBox *tbx_arac{};
    QToolBox *tbx_evrk{};
    QToolBox *tbx_bkm{};
    QToolBox *tbx_clsm{};
    QToolBox *tbx_arz{};

    //Evr_Sgrt *evrk_sgrt{};
    //Evr_Mua *evrk_mua{};

    int idx_mkcins{};	//
    int idx_mkmark{};	//
    int idx_mkmdl{};	//

    // models
    //QSqlRelationalTableModel *MKNmodel{};
    QSqlRelationalTableModel *CLSNmodel{};
    QSqlRelationalTableModel *mdl_mkcins{};
    QSqlRelationalTableModel *mdl_mkmark{};
    QSqlRelationalTableModel *mdl_mkmodl{};

    //    QPushButton *getPb_mknByer() const;
    //  void setPb_mknByer(QPushButton *value);



signals:
    void sgnMkn (const QString);
};


#endif // hC_MKN_H
