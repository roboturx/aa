#ifndef HC_MLZM_H
#define HC_MLZM_H


#include "globals.h"

namespace nSMlzm {
class hC_MLZM;
}

class hC_MLZM : public QWidget
{   Q_OBJECT

public:

    void    mlzm_setup () ;
    QString mlzm_VTd   () ;
    void    mlzm_model () ;


    hC_Tv                    *MLZMtview    {} ;
    QSqlRelationalTableModel *MLZMmodel    {} ;
    QItemSelectionModel      *MLZMslctnMdl {} ;
    QDataWidgetMapper        *MLZMmapper   {} ;

    QWidget * mlzmWdgt {} ;
    QLabel  * lB_mlzm     {} ;
    QLabel  * lB_mlzmrsm  {} ;


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


private:
    void mlzm_ui    () ;
    void mlzm_Wdgt  () ;
    void mlzm_view  () ;
    void mlzm_map   () ;
    void mlzm_kntrl () ;


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

#endif // HC_MLZM_H
