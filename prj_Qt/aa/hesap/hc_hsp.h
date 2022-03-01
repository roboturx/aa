#ifndef hC_HSP_H
#define hC_HSP_H

#include "main/globals.h"
namespace nSHsp
{
class hC_HSP;
}
class hC_HSP : public hC_tBcreator
{
    Q_OBJECT
public:
    explicit hC_HSP();
    ~hC_HSP();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QLineEdit   *lE_ad=nullptr    ;
    QDateEdit   *dE_tarih=nullptr   ;
    QLineEdit   *lE_aciklama{};
    QComboBox   *cB_parabrm=nullptr;
    QLineEdit   *lE_not{};
    QLineEdit   *lE_gizli{};
    QLineEdit   *lE_toplu{}   ;
    QComboBox   *cB_turu{}   ;
    QComboBox   *cB_ust{}   ;


    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

protected:
    void showEvent(QShowEvent *);



};

#endif // hC_HSP_H
