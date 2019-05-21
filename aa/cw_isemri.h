#ifndef CW_ISEMRI_H
#define CW_ISEMRI_H

#include <globals.h>


/////////////////////////////////////////
///
/// class
/// iş emri
///



namespace Ui {
class Cw_IsEmri;
}

class Cw_IsEmri : public QWidget
{
    Q_OBJECT

public:
    explicit Cw_IsEmri(QWidget *parent = nullptr);
    ~Cw_IsEmri();

public:

    // IE    -  İş Emri
    // IEDET -  İş Emri Detay
    // TS    -  Taşınır
    // SC    -  İşçilik

    QLabel *lbl_mkn;
    QLabel *lbl_IE;

    QSqlRelationalTableModel *IEmodel;
    QSqlRelationalTableModel *IEDETmodel;
    QSqlRelationalTableModel *TSmodel;
    QSqlRelationalTableModel *SCmodel;
    QItemSelectionModel *IEtV_selectionMdl ;

    QTableView *IEtview ;
    QTableView *IEDETtview ;
    QTableView *TStview;
    QTableView *SCtview;

        QDataWidgetMapper *IEmapper;
        QDataWidgetMapper *IEDETmapper;
        QDataWidgetMapper *TSmapper;
        QDataWidgetMapper *SCmapper;
    /// iedet variables

    QWidget *wdgt_IEdetekle;
    QWidget *wdgt_TSekle;
    QWidget *wdgt_SCekle;

    QString *IEno;
    QString *IE_idno;
    QString *IEdetno;
    QLineEdit *lE_IEdetno ;
    QLineEdit *lE_IEdetaciklama ;

    QComboBox *cbx_IEdettamiryeri ;
    QComboBox *cbx_IEdetkurumicdis ;      // dbtb_clsn

    QComboBox *cbx_IEdetdurum ;
    void clk_IEdetdurum();
    void clk_IEdetclsn();

    QDateTimeEdit *dE_IEdetgirtarihi ;
    QDateTimeEdit *dE_IEdetciktarihi ;

    QComboBox *cbx_IEdetyapyer ;
    void clk_IEdetyyer();
    QDateTimeEdit *dE_IEdettarih;

    void clk_IEdetkaydet();

    // TS variable
    QComboBox *cbx_TSmlzm;
    QSqlTableModel *cbxTSmlzmModel ;

    QLineEdit *lE_TSno;
    QDateTimeEdit *dE_TStarih;
    QComboBox *cbx_TSmalzeme;
    QLineEdit *lE_TSmiktar;
    QComboBox *cbx_TSbirim;
    QLineEdit *lE_TSbfiyat;
    QComboBox *cbx_TSdurum;
    QLineEdit *lE_TSaciklama;
    QString *TSdet_idno;
    QString *TSdetno;
    QString *TSno;


    // SC variable
    QLineEdit *lE_SCno;
    QDateTimeEdit *dE_SCtarih;
    QComboBox *cbx_SCbirim;
    QComboBox *cbx_SCusta;
    QLineEdit *lE_SCsaat;
    QLineEdit *lE_SCucret;
    QComboBox *cbx_SCucrettip;
    QLineEdit *lE_SCaciklama;
    QString *SCdet_idno;
    QString *SCdetno;
    QString *SCno;

private:
    void setup_ui();
   // void setup_uidet();

    void model_IE();
    void model_IEDET();
    void model_TASINIR();
    void model_ISCILIK();

    void view_IE();
    void view_IEDET();
    void view_TASINIR();
    void view_ISCILIK();

    void kontrolIE();


    QGridLayout *gL;
    QGridLayout *gLdet;
    QHBoxLayout *hL1 ;
    QHBoxLayout *hL2 ;
    QPushButton *pB1 ;
    QPushButton *pB2 ;
    QPushButton *pB3 ;
    QPushButton *pB4 ;
    QPushButton *pB5 ;
    QPushButton *pB6 ;
    QPushButton *pB7 ;


public slots:
    void rowChanged_IE(QModelIndex IEindex);
    void rowChanged_IEDET(QModelIndex IEDETindex);



    void clk_IEDETbosh();
    void clk_TSbosh();
    void clk_SCbosh();

private slots:

    void onmnIE_IEDETekle();
    void onmnIEDET_TSekle();
    void onmnIEDET_SCekle();

    void rowChanged_TASINIR(QModelIndex);
    void rowChanged_ISCILIK(QModelIndex);

    void rightMenu_IE(QPoint pos);
    void rightMenu_IEDET(QPoint pos);
    void rightMenu_TASINIR(QPoint pos);
    void rightMenu_ISCILIK(QPoint pos);


    //void ekle_IE(); // mknde ekleniyor

    void IEDETekle();
    void TSekle();
    void SCekle();



    void sil_IE();
    void sil_IEDET();
    void sil_TASINIR();
    void sil_ISCILIK();

    void ayar_ISCILIK();

};



#endif // CW_ISEMRI_H
