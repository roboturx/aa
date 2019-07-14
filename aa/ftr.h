#ifndef CW_FTR_H
#define CW_FTR_H


#include "globals.h"

namespace nSFtr {
class hC_FTR;
}

class hC_FTR : public QWidget
{
    Q_OBJECT

public:
    explicit hC_FTR(QWidget *parent = nullptr);
    ~hC_FTR() ;

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

    QLabel      * lB_brkd{} ;
    QLineEdit   * lE_faturano{}  ;
    hC_Le       * lE_firma{} ;
    QLineEdit   * lE_tarih{};
    QLineEdit   * lE_aciklama{};
QLineEdit   * lE_ftrToplam;
QLineEdit   * lE_ftrKdv;
QLineEdit   * lE_ftrGenelToplam;


    void setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;


signals:
    void sgnFtr ( QString* sgnFtrNo ); // ftr bilgisi yayınla

private slots:
    void slt_ftr_hesap();

protected:
    void showEvent(QShowEvent *);

};

#endif // CW_FTR_H
