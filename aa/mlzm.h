#ifndef HC_MLZM_H
#define HC_MLZM_H


#include "globals.h"

namespace nSMlzm {
class hC_MLZM;
}

class hC_MLZM : public QWidget
{   Q_OBJECT

public:
/////////////////////////////////////////////////
    hC_Tv                    * tb_view     {} ;
    QSqlRelationalTableModel * tb_model     {} ;
    QItemSelectionModel      * tb_slctnMdl {} ;
    QDataWidgetMapper        * tb_mapper   {} ;

    QString                  * tb_name     {} ;
    hC_ArrD                  * tb_flds     {} ;
    QString                  * tb_ndex     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QWidget                  * win_Wdgt  {} ;
    QLabel                   * win_Label {} ;
    QLabel                   * win_Rsm   {} ;
/////////////////////////////////////////////////

    QComboBox   *cbx_grs_tipi{} ;
    QLineEdit   *lE_barkod   {} ;
    QLineEdit   *lE_malzeme  {} ;
    QLineEdit   *lE_aciklama {} ;
    QLineEdit   *lE_marka    {} ;
    QLineEdit   *lE_model    {} ;
    QLineEdit   *lE_cins     {} ;
    QComboBox   *cbx_birim   {} ;
    QLineEdit   *lE_giris    {} ;
    QLineEdit   *lE_cikis    {} ;
    QLineEdit   *lE_mevcut   {} ;

    void setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;


private slots:
    void slt_Mlzm_hesap(QModelIndex Index);

protected:
    void showEvent(QShowEvent *);

signals:
    void sgnMalzeme (QString* sgnKod,
                     QString* sgnBarkod,
                     QString* sgnMalzeme,
                     QString* sgnBirim
                     ); //malzeme ismini yayınla

public:
    explicit hC_MLZM(QWidget *parent = nullptr);
    ~hC_MLZM();
};

#endif // HC__H
