#ifndef MKN_MODELI_H
#define MKN_MODELI_H

#include "globals.h"
//#include "hc_.h"
//#include "dbase.h"
//#include "ftr_frmekle.h"
namespace Ui {
    class hC_MKMODL;
}

class hC_MKMODL : public QDialog
{
    Q_OBJECT

public:
    explicit hC_MKMODL(QDialog *parent = nullptr);
    ~hC_MKMODL();


    QString sgnText{};

    //DBase *dbase;
    QString mkmodl_VTd();
    void mkmodl_setup();
    void mkmodl_model(QSqlRelationalTableModel *model) ;


    QLabel *lB_rsm;

    hC_Tv            *MDLtview{};
    QSqlRelationalTableModel *MDLmodel{} ;
    QItemSelectionModel      *MDLselectionMdl;
    QDataWidgetMapper        *MDLmapper;

private:

    void set_uiMDL();

    void set_modelMDL();
    void set_viewMDL();
    void set_mapMDL();
    void set_kntrlMDL();



signals:
    void sgnCmmy (const QString);
};



#endif // MKN_MODELI_H
