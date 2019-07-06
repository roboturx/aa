#ifndef MKN_CINSI_H
#define MKN_CINSI_H


#include "globals.h"
//#include "hc_.h"
//#include "dbase.h"
//#include "ftr_frmekle.h"
namespace nSMkn {
    class hC_MKCINS;
}

class hC_MKCINS : public QDialog
{
    Q_OBJECT

public:
    explicit hC_MKCINS(QDialog *parent = nullptr);
    ~hC_MKCINS();

    hC_Tv                    * CNStview    {} ;
    QSqlRelationalTableModel * CNSmodel    {} ;
    QItemSelectionModel      * CNSslctnMdl {} ;
    QDataWidgetMapper        * CNSmapper   {} ;

    QWidget * winWdgt    {} ;
    QLabel  * winLabel   {} ;
    QLabel  * winRsm     {} ;
    QString * sgnText    {} ;

    void    mkCins_setup () ;
    QString mkCins_VTd   () ;
    void    mkCins_model () ;

private:
    void mkCins_wdgt  () ;
    void mkCins_map   () ;
    void mkCins_ui    () ;
    void mkCins_view  () ;
    void mkCins_kntrl () ;


signals:
    void sgnCmmy (QString* sgnCmm);
};

#endif // MKN_CINSI_H

