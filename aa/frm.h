#ifndef CW_FR_H
#define CW_FR_H

#include "globals.h"
#include "hc_.h"
#include "dbase.h"



namespace ns_FRM {
class hC_FRM;
}

class hC_FRM : public QWidget
{
    Q_OBJECT

public:
    explicit hC_FRM(QWidget *parent = nullptr);
    ~hC_FRM();

    void    frm_setup();
    QString frm_VTd();
    void    frm_model(QSqlRelationalTableModel * );

    QString *FRMtableName {};

    //DBase *dbase;
    hC_Tv*                    FRMtview ;
    QSqlRelationalTableModel* FRMmodel {} ;
    QItemSelectionModel*      FRMselectionMdl;
    QDataWidgetMapper*        FRMmapper {};

    int       meslekIndex{} ;
    QComboBox   *cb_meslek{};
    QGroupBox   *gB_map{}   ;
    QLabel      *lB_fr{}    ;
    QLabel      *lB_rsm{}   ;
    QLineEdit   *lE_unvan{} ;
    QLineEdit   *lE_adres{} ;
    QLineEdit   *lE_sehir{} ;
    QLineEdit   *lE_vd{}    ;
    QLineEdit   *lE_vdno{}  ;
    QLineEdit   *lE_tel{}   ;
    QLineEdit   *lE_eposta{};
    QLineEdit   *lE_yisim{} ;
    QLineEdit   *lE_ysoyad{};
    QLineEdit   *lE_ytel{}  ;

   // QPushButton *pB_rsm{}     ;
  //  QPushButton *pB_ekle{}    ;
  //  QPushButton *pB_sil{}     ;

  //  QPushButton *pB_ara{}     ;
  //  QPushButton *pB_yaz{}     ;
  //  QPushButton *pB_kpt{}     ;

private:
    void frm_ui()   ;
    void frm_view() ;
    void frm_map()  ;
    void frm_kntrl();

signals:
    void sgnfirma (const QString sgnfirma); //firma ismini

protected:
    void showEvent(QShowEvent *);
};

#endif // CW_FR_H



