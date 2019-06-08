#ifndef CW_FR_H
#define CW_FR_H

#include "globals.h"
#include "hc_tableview.h"
#include "dbase.h"



namespace Ui {
class Cw_fr;
}

class Cw_fr : public QWidget
{
    Q_OBJECT

public:
    explicit Cw_fr(QWidget *parent = nullptr);
    ~Cw_fr();

    void setup_firma();
    DBase *dbase;

    QModelIndex *whichRow{};
    QDataWidgetMapper *FRMmapper {};
    QSqlTableModel *FRMmodel {} ;
    HC_TableView  *FRMtview ;
    QItemSelectionModel *FRMselectionMdlxxx;


    int         meslekIndex{} ;

    QComboBox   *cb_meslek{}  ;

    QGroupBox   *gB_map{}     ;

    QLabel      *lB_fr{}    ;
    QLabel      *lB_rsm{}    ;


    QLineEdit   *lE_unvan{}    ;
    QLineEdit   *lE_adres{}   ;
    QLineEdit   *lE_sehir{};
    QLineEdit   *lE_vd{};

    QLineEdit   *lE_vdno{};
    QLineEdit   *lE_tel{} ;
    QLineEdit   *lE_eposta{} ;
    QLineEdit   *lE_yisim{} ;
    QLineEdit   *lE_ysoyad{}   ;
    QLineEdit   *lE_ytel{} ;

    QPushButton *pB_rsm{}     ;
    QPushButton *pB_ekle{}    ;
    QPushButton *pB_sil{}     ;

    QPushButton *pB_ara{}     ;
    QPushButton *pB_yaz{}     ;
    QPushButton *pB_kpt{}     ;

private:


    void setup_ui()        ;
    void setup_modelfr()  ;
    void setup_viewfr()   ;
    void setup_mapfr()   ;

private slots:

signals:

    void sgnfirma (const QString sgnfirma); //firma ismini

protected:
    void showEvent(QShowEvent *);
};

#endif // CW_FR_H



