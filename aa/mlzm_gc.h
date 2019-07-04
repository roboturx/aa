#ifndef MLZM_GC_H
#define MLZM_GC_H


#include "globals.h"
#include "ftr.h"
#include "mlzm.h"
namespace nSMlzmGC {
class hC_MLZMGC;
}

class hC_MLZMGC : public QWidget
{   Q_OBJECT

public:

    // MlzmGc
    void    mlzmGc_setup () ;
    QString mlzmGc_VTd   () ;
    void    mlzmGc_model () ;

    hC_Tv                    *MLZMGCtview        {} ;
    QItemSelectionModel      *MLZMGCselectionMdl {} ;
    QSqlRelationalTableModel *MLZMGCmodel        {} ;
    QDataWidgetMapper        *MLZMGCmapper       {} ;

    hC_MLZM     *mlzm         {} ;
    QString     *mlzmKod      {} ;
    QString     *mlzmBarkod   {} ;
    QString     *mlzmMalzeme  {} ;
    QString     *mlzmBirim    {} ;

    QWidget     *mlzmGcWdgt   {} ;
    QLabel      *lB_mlzmGc    {} ;

    QLineEdit   *lE_barkod    {} ;
    QLineEdit   *lE_malzeme   {} ;
    QLineEdit   *lE_tarih     {} ;
    QComboBox   *cbx_grscks   {} ;
    QLineEdit   *lE_miktar    {} ;
    QLineEdit   *lE_fiyat     {} ;
    QLineEdit   *lE_aciklama  {} ;
    QLabel      *lB_mlzmGcrsm {} ;


private:

    void mlzmGc_ui() ;
    void mlzmGc_wdgt()   ;
    void mlzmGc_view() ;
    void mlzmGc_map() ;
    void mlzmGc_kntrl();


protected:
    void showEvent(QShowEvent *);

public:
    explicit hC_MLZMGC(QWidget *parent = nullptr);
    ~hC_MLZMGC();
};


/*

// ////////////////////////////////////////////// Fatura detaya malzeme ekle
class FtrDet_MlzEkle : public QDialog
{
    Q_OBJECT

public:
    explicit FtrDet_MlzEkle(QDialog *parent = nullptr);
    ~FtrDet_MlzEkle();

    QString getMalzeme() const;
    hC_MLZM  *malzeme;
protected:
    void reject() ;
private:
    QString m_malzeme;
    void setMalzeme(const QString &value);
};
*/




#endif // MLZM_GC_H
