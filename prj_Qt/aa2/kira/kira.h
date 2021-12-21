#ifndef hC_KIRA_H
#define hC_KIRA_H

#include "main/globals.h"

namespace nSKira {
class hC_KIRA;
}

class hC_KIRA : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_KIRA();
    ~hC_KIRA();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QDateEdit   *dE_duztar{};
    QLineEdit   *lE_duzno=nullptr    ;
    QLineEdit   *lE_kvtc=nullptr   ;
    QLineEdit   *lE_kctc=nullptr;
    QLineEdit   *lE_adkod{};
    QDateEdit   *dE_kbastar{};
    QDateEdit   *dE_kbttar{}   ;
    QLineEdit   *lE_sure{}   ;

    QLineEdit   *lE_bedel{}   ;
    QLineEdit   *lE_teminat{}   ;
    QLineEdit   *lE_osekli{}   ;
    QLineEdit   *lE_hesno{} ;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

protected:
    void showEvent(QShowEvent *);

};

#endif // hC_KIRA_H
