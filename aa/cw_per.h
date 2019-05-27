#ifndef CW_PER_H
#define CW_PER_H

//#include <QPushButton>
#include "globals.h"
//#include "cw_map_per.h"
namespace Ui {
class Cw_per;
}

class Cw_per : public QWidget
{   Q_OBJECT

public:
    QModelIndex *whichRow=nullptr ;
    QDataWidgetMapper *map_per=nullptr;
    QSqlTableModel *mdl_per=nullptr ;

    int         meslekIndex=0 ;

    QComboBox   *cb_meslek=nullptr  ;

    QGroupBox   *gB_map=nullptr     ;

    QLabel      *lB_per=nullptr    ;
    QLabel      *lB_rsm=nullptr    ;
      

    QLineEdit   *lE_isim=nullptr    ;
    QLineEdit   *lE_soyad=nullptr   ;
    QLineEdit   *lE_tc=nullptr;
    QLineEdit   *lE_doyer;
    QDateEdit *dT_dotar;
    QLineEdit   *lE_baba;
    QLineEdit   *lE_bolum   ;
    QLineEdit   *lE_gorev   ;
    QLineEdit   *lE_adres   ;
    QLineEdit   *lE_sehir   ;
    QLineEdit   *lE_tel_cep ;
    QLineEdit   *lE_tel_ev  ;
    QLineEdit   *lE_eposta  ;
    QLineEdit   *lE_username;
    QLineEdit   *lE_password;
    QLineEdit   *lE_yetki   ;

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

public:
    void setup_modelPer()  ;

private:
    QTableView  *tV_per     ;

    void setup_ui()        ;

    void setup_viewPer()   ;
    void setup_map()   ;

private slots:
    void on_pB_KPT_clicked();
    void on_pB_ARA_clicked();
    void on_pB_YAZ_clicked();
    void on_pB_SIL_clicked();
    void on_pB_EKLE_clicked();
    void ontV_per_resimGosterSLOT(QModelIndex);
    void onpB_per_resimEklE_clickedSLOT();
    void r_toFirst();
    void r_toPrevious();
    void r_toNext();
    void r_toLast();

   // void resim(QModelIndex);
    void on_updateButtonsSLOT(int row);


protected:
    void showEvent(QShowEvent *);

public:
    explicit Cw_per(QWidget *parent = 0);
    ~Cw_per();
};

#endif // CW_PER_H
