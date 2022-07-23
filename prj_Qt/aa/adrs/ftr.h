#ifndef CW_FTR_H
#define CW_FTR_H


#include "libs/globals.h"


namespace nSFtr {
class hC_FTR;
}

class hC_FTR : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_FTR();
    ~hC_FTR() ;

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;


    QLabel      * lB_brkd{} ;
    QLineEdit   * lE_faturano{}  ;
    hC_Le       * hClE_firma{} ;
    QLineEdit   * lE_tarih{};
    QLineEdit   * lE_aciklama{};
QLineEdit   * lE_ftrToplam;
QLineEdit   * lE_ftrKdv;
QLineEdit   * lE_ftrGenelToplam;


void tbsetup () ;

private:
void tbwdgt  () ;
void tbui    () ;
void tbkntrl () ;


signals:
    void sgnFtr ( QString* sgnFtrNo ); // ftr bilgisi yayınla

private slots:
    void slt_ftr_hesap();

protected:
    void showEvent(QShowEvent *);

};

#endif // CW_FTR_H
