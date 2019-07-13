#ifndef MKN_MODELI_H
#define MKN_MODELI_H

#include "globals.h"

namespace nSMkn {
    class hC_MKMODL;
}

class hC_MKMODL : public QDialog
{
    Q_OBJECT

public:
    explicit hC_MKMODL(QDialog *parent = nullptr);
    ~hC_MKMODL();
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

    void setup () ;

private:
    void wdgt  () ;
    void ui    () ;
    void kntrl () ;

signals:
    void sgnmkModl (QString*);
};



#endif // MKN_MODELI_H
