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
    QString * sgnText  {} ;

    void    mkMark_setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;

signals:
    void sgnmkMark (QString*);
};

#endif // MKN_MARKA_H
