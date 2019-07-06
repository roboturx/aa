#ifndef CW_FR_H
#define CW_FR_H

#include "globals.h"

namespace nSFrm {
class hC_FRM;
}

class hC_FRM : public QWidget
{
    Q_OBJECT

public:
    explicit hC_FRM(QWidget *parent = nullptr);
    ~hC_FRM();

    hC_Tv                    * FRMtview    {} ;
    QSqlRelationalTableModel * FRMmodel    {} ;
    QItemSelectionModel      * FRMslctnMdl {} ;
    QDataWidgetMapper        * FRMmapper   {} ;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel    {} ;
    QLabel  * winRsm   {} ;

    int       meslekIndex{} ;
    QComboBox   *cb_meslek{};
    QGroupBox   *gB_map{}   ;
    QLabel      *lB_fr{}    ;

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

    void    frm_setup();
    QString frm_VTd();
    void    frm_model();

    //QString *FRMtableName {};

private:
    void frm_wdgt  () ;
    void frm_map   () ;
    void frm_ui    () ;
    void frm_view  () ;
    void frm_kntrl () ;

signals:
    void sgnfirma (const QString sgnfirma); //firma ismini

protected:
    void showEvent(QShowEvent *);
};

#endif // CW_FR_H



