#ifndef MKN_CINSI_H
#define MKN_CINSI_H


#include "globals.h"

namespace nSMkn {
    class hC_MKCINS;
}

class hC_MKCINS : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_MKCINS();
    ~hC_MKCINS();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QString * sgnText    {} ;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;


signals:
    void sgnCmmy (QString* sgnCmm);
};

#endif // MKN_CINSI_H

