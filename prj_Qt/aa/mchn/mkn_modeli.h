#ifndef MKN_MODELI_H
#define MKN_MODELI_H

#include "libs/globals.h"

namespace nSMkn {
    class hC_MKMODL;
}

class hC_MKMODL : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_MKMODL();
    ~hC_MKMODL();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QString * sgnText  {} ;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

signals:
    void sgnmkModl (QString*);
};



#endif // MKN_MODELI_H
