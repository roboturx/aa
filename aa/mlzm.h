#ifndef HC_MLZM_H
#define HC_MLZM_H


#include "globals.h"

namespace nSMlzm {
class hC_MLZM;
}

class hC_MLZM : public QWidget
{   Q_OBJECT

public:

    hC_Tv                    * tB_view     {} ;
    QSqlRelationalTableModel * tB_modl     {} ;
    QItemSelectionModel      * tB_slctnMdl {} ;
    QDataWidgetMapper        * tB_map      {} ;

    QString                  * tB_name     {} ;
    hC_ArrD                  * tB_fields   {} ;
    QString                  * tB_ndex     {} ;

    QVector<QWidget*>        * win_wdgts {} ;
    QWidget                  * win_Wdgt  {} ;
    QLabel                   * win_Label {} ;
    QLabel                   * win_Rsm   {} ;

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

    void    setup () ;
    QString VTd   (QString *tB_name, hC_ArrD *tB_fields  ) ;
    void    model () ;

private:
    void wdgt  () ;
    void map   () ;
    void ui    () ;
    void view  () ;
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
