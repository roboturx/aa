#ifndef HC_MLZM_H
#define HC_MLZM_H


#include "globals.h"

namespace nSMlzm {
class hC_MLZM;
}

class hC_MLZM : public QWidget
{   Q_OBJECT

public:

    hC_Tv                    *MLZMtview    {} ;
    QSqlRelationalTableModel *tB_modl    {} ;
    QItemSelectionModel      *MLZMslctnMdl {} ;
    QDataWidgetMapper        *MLZMmapper   {} ;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel {} ;
    QLabel  * winRsm   {} ;
    QVector < QVector < QString > > * fields ;
    QStringList *tB_fieldList {} ;
    QString *tB_name   {} ;
    QString *tB_ndex   {} ;

   // QVector<QStringList>* fields;

    //QMap<QString,QString> * fields ;
    QVector<QWidget*> * edits  ;

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

    void    mlzm_setup () ;
    QString mlzm_VTd   () ;
    void    mlzm_model () ;

private:
    void mlzm_wdgt  () ;
    void mlzm_map   () ;
    void mlzm_ui    () ;
    void mlzm_view  () ;
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
