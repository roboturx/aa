#ifndef MLZM_GC_H
#define MLZM_GC_H


#include "globals.h"
#include "ftr.h"
#include "mlzm.h"
namespace nSMlzmGC {
class hC_tb_;
}

class hC_MLZMGC : public QWidget
{   Q_OBJECT

public:

    explicit hC_MLZMGC(QWidget *parent = nullptr);
    ~hC_MLZMGC();

    ////////////////////////////////////////////////
    hC_Tv                    * tb_view    {} ;
    QItemSelectionModel      * tb_slctnMdl {} ;
    QSqlRelationalTableModel * tb_model    {} ;
    QDataWidgetMapper        * tb_mapper   {} ;


    QString                  * tb_name     {} ;
    hC_ArrD                  * tb_flds   {} ;
    QString                  * tb_ndex     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QWidget                  * win_Wdgt  {} ;
    QLabel                   * win_Label {} ;
    QLabel                   * win_Rsm   {} ;
/////////////////////////////////////////////////

    hC_MLZM     *mlzm         {} ;
    QString     *mlzmKod      {} ;
    QString     *mlzmBarkod   {} ;
    QString     *mlzmMalzeme  {} ;
    QString     *mlzmBirim    {} ;

    QWidget     *mlzmGcWdgt   {} ;

    QLineEdit   *lE_barkod    {} ;
    QLineEdit   *lE_malzeme   {} ;
    QLineEdit   *lE_tarih     {} ;
    QComboBox   *cbx_grscks   {} ;
    QLineEdit   *lE_miktar    {} ;
    QLineEdit   *lE_fiyat     {} ;
    QLineEdit   *lE_aciklama  {} ;


    void setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;


protected:
    void showEvent(QShowEvent *);


};

#endif // MLZM_GC_H
