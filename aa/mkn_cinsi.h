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
    ////////////////////////////////////////////////
    hC_Tv                    * tb_view    {} ;
    QItemSelectionModel      * tb_slctnMdl {} ;
    QSqlRelationalTableModel * tb_model    {} ;
    QDataWidgetMapper        * tb_mapper   {} ;


    QString                  * tb_name     {} ;
    hC_ArrD                  * tb_flds   {} ;
    QString                  * tb_ndex     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QWidget                  * win_Wdgt  {} ;
    QLabel                   * win_Label {} ;
    QLabel                   * win_Rsm   {} ;
/////////////////////////////////////////////////

    QString * sgnText    {} ;

    void    mkCins_setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;


signals:
    void sgnCmmy (QString* sgnCmm);
};

#endif // MKN_CINSI_H

