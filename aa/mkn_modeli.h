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

    hC_Tv            *MDLtview{};
    QSqlRelationalTableModel *MDLmodel{} ;
    QItemSelectionModel      *MDLslctnMdl;
    QDataWidgetMapper        *MDLmapper;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel {} ;
    QLabel  * winRsm   {} ;
    QString * sgnText  {} ;


    void    mkModl_setup () ;
    QString mkModl_VTd   () ;
    void    mkModl_model () ;

private:
    void mkModl_wdgt  () ;
    void mkModl_map   () ;
    void mkModl_ui    () ;
    void mkModl_view  () ;
    void mkModl_kntrl () ;

signals:
    void sgnmkModl (QString*);
};



#endif // MKN_MODELI_H
