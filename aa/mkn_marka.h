#ifndef MKN_MARKA_H
#define MKN_MARKA_H

#include "globals.h"
//#include "hc_.h"
//#include "dbase.h"
//#include "ftr_frmekle.h"

namespace nSMkn {
    class hC_MKMARK;
}

class hC_MKMARK : public QDialog
{
    Q_OBJECT

public:
    explicit hC_MKMARK(QDialog *parent = nullptr);
    ~hC_MKMARK();

    hC_Tv                    * MRKtview    {} ;
    QSqlRelationalTableModel * MRKmodel    {} ;
    QItemSelectionModel      * MRKslctnMdl {} ;
    QDataWidgetMapper        * MRKmapper   {} ;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel {} ;
    QLabel  * winRsm   {} ;
    QString * sgnText  {} ;

    void    mkMark_setup () ;
    QString mkMark_VTd   () ;
    void    mkMark_model () ;


private:
    void mkMark_wdgt  () ;
    void mkMark_map   () ;
    void mkMark_ui    () ;
    void mkMark_view  () ;
    void mkMark_kntrl () ;

signals:
    void sgnmkMark (QString*);
};

#endif // MKN_MARKA_H
