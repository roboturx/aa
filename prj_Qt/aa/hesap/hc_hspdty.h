#ifndef hC_HSPDTY_H
#define hC_HSPDTY_H

#include "main/globals.h"
namespace nSHspDty
{
class hC_HSPDTY;
}
class hC_HSPDTY : public hC_tBcreator
{
    Q_OBJECT
public:
    explicit hC_HSPDTY();
    ~hC_HSPDTY();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QLineEdit   *lE_ad=nullptr    ;
    QDateEdit   *dE_tarih=nullptr   ;
    QLineEdit   *lE_no=nullptr;
    QLineEdit   *lE_aciklama{};
    QComboBox   *cB_aktar{};
    QLineEdit   *lE_ok{};
    QLineEdit   *lE_borc{}   ;
    QLineEdit   *lE_alacak{}   ;
    QLineEdit   *lE_bakiye{}   ;


    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

protected:
    void showEvent(QShowEvent *);



};

#endif // hC_HSPDTY_H
