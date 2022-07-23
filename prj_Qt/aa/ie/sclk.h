#ifndef SCLK_H
#define SCLK_H

#include "libs/globals.h"
//#include "hc_.h"

namespace nSSclk {
class hC_SCLK;
}

class hC_SCLK : public  hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_SCLK();
    ~hC_SCLK();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QLineEdit *lE_SCno{};
    QDateTimeEdit *dE_SCtarih{};
    QLineEdit *lE_SCbirim{};
    QLineEdit *lE_SCusta{};
    QLineEdit *lE_SCsaat{};
    QLineEdit *lE_SCucret{};
    QComboBox *cbx_SCucrettip{};
    QLineEdit *lE_SCaciklama{};
    QString *SCdet_idno{};
    QString *SCdetno{};
    QString *SCno{};

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

};

#endif // SCLK_H
