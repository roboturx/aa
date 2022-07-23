#ifndef MKN_MARKA_H
#define MKN_MARKA_H

#include "libs/globals.h"
//#include "hc_.h"
//#include "dbase.h"
//#include "ftr_frmekle.h"

namespace nSMkn {
    class hC_MKMARK;
}

class hC_MKMARK : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_MKMARK();
    ~hC_MKMARK();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QString * sgnText  {} ;

    void tbsetup () ;

private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;

signals:
    void sgnmkMark (QString*);
};

#endif // MKN_MARKA_H
