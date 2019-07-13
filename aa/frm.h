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

    ////////////////////////////////////////////////
    hC_Tv                    * tb_view     {} ;
    QItemSelectionModel      * tb_slctnMdl {} ;
    QSqlRelationalTableModel * tb_model    {} ;
    QDataWidgetMapper        * tb_mapper   {} ;

    QString                  * tb_name     {} ;
    hC_ArrD                  * tb_flds     {} ;
    QString                  * tb_ndex     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QWidget                  * win_Wdgt    {} ;
    QLabel                   * win_Label   {} ;
    QLabel                   * win_Rsm     {} ;
/////////////////////////////////////////////////

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

    void setup();

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;

signals:
    void sgnfirma (const QString sgnfirma); //firma ismini

protected:
    void showEvent(QShowEvent *);
};

#endif // CW_FR_H



