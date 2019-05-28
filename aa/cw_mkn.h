#ifndef Cw_mkn_H
#define Cw_mkn_H

#include "globals.h"
#include "cw_grs.h"
#include "cw_isemri.h"

#include "mkevrk.h"

class SKGComboBox;
namespace Ui {
class Cw_mkn;
}

class Cw_mkn : public QWidget
{
    Q_OBJECT
public:
    explicit Cw_mkn(QWidget *parent = nullptr);
    ~Cw_mkn();

    
    QSqlRelationalTableModel * mkn_model();
    

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
    void onMKNtview_resimGosterSLOT(QModelIndex);
    void resimEkle();
    void mknKurumno_ara();
private slots:

    //////////////////////////////////////////// tableview SLOTS

    void onMKNtview_sagmenuSLOT(QPoint pos);
    /// makina table view sağ menu SLOTLARI
    void onmnMKN_MKNekle();
    void onmnMKN_IEekle();

    //    void mknekle();
    void onmnMKN_resimEklE_clickedSLOT();
    void onmnMKN_arac_sil_clickedSLOT();





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


    void onMKNtview_IE_filterSLOT(QModelIndex mknIndex);
    //  void onMKNtview_resimGosterSLOT(QModelIndex);
    void onMKNtview_cmm_filterSLOT(QModelIndex);
    //  void onMKNtview_IE_det_filterSLOT(QModelIndex);

    ///////////////////////////////////////////// pushbutton SLOTS
    void onpb_mknclickedSLOT();
    void onpb_tabclickedSLOT();
    void onpb_resimPencereSLOT();
    void clk_boshMKN();
    void MKNekle();
    void clk_boshIE();
    void IEekle();

    ///////////////////////////////////////////// combobox SLOTS



    ///////////////////////////////// others
    // void oncbx_mknCinsclickedSLOT(const QString&);
    void ww_mkcins();

public:

    // ui
    QTableView *MKNtview{};
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

    QComboBox *cbx_mknCins{};
    QSqlTableModel *cbxCinsiModel{};// dbtb_cins
    QPushButton *pb_mknCins{};


    QComboBox *cbx_mknMark{};
    QSqlTableModel *cbxMarkaModel{};// dbtb_mknMarka
    QPushButton *pb_mknMark{};
    //void oncbx_mknMarkclickedSLOT();


    QComboBox *cbx_mknModl{};
    QSqlTableModel *cbxModeliModel{};// dbtb_model
    QPushButton *pb_mknModl{};


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

    QLineEdit *led_dp_no{};

    QLabel *lB_resim{};

    QByteArray *rsm_ByteArray{} ;

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


    QDataWidgetMapper *mppMKN{};


    QWidget *wdgt_mppr{};
    QWidget *wdgt_sol{};
    QWidget *wdgt_tv{};
    QWidget *wdgt_rsm{};

    QLabel *lB_foto{};

    QPushButton *pb_rsmEkle{};
    QPushButton *pb_rsm{};





    QTabWidget *wtab{};

    QString SS01;
    QString SS02;

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

    Cw_Grs *Cwv_Grs{} ;
    Cw_IsEmri *Cwv_IsEmri{} ;
    //Cw_IEdet *Cwv_IEdet ;
    //Cw_tasinir *Cwv_Tasinir;

    Evr_Sgrt *evrk_sgrt{};
    Evr_Mua *evrk_mua{};

    int idx_mkcins{};	//
    int idx_mkmark{};	//
    int idx_mkmdl{};	//

    // models
    QSqlRelationalTableModel *MKNmodel{};
    QSqlRelationalTableModel *CLSNmodel{};
    QSqlRelationalTableModel *mdl_mkcins{};
    QSqlRelationalTableModel *mdl_mkmark{};
    QSqlRelationalTableModel *mdl_mkmodl{};

    //    QPushButton *getPb_mknByer() const;
    //  void setPb_mknByer(QPushButton *value);
};
class __attribute__
        ((visibility("default")))
            SKGComboBox :
               public QComboBox
{
Q_OBJECT
Q_PROPERTY( QString text READ text WRITE setText USER true)

public:
/**
* Default Constructor
*/
SKGComboBox(QWidget *parent = nullptr);

/**
* Default Destructor
*/
virtual ~SKGComboBox();

/**
* Get the text for the combo
* @return the text
*/
virtual QString text() const;


/**
* Set the text for the combo
* @param iText the text
*/
virtual void setText (const QString& iText);


};


#endif // Cw_mkn_H
