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




    QString sgnText ;

    void mkcins_setup();
    QString mkcins_VTd();
    void mkcins_model(QSqlRelationalTableModel *model);

    //DBase *dbase;

    QLabel *lB_rsm;
    hC_Tv             *CNStview{};
    QSqlRelationalTableModel *CNSmodel{} ;
    QItemSelectionModel      *CNSslctnMdl;
    QDataWidgetMapper        *CNSmapper;

private:

    void set_uiCNS();
    //void modelCinsi();
    void set_viewCNS();
    void set_mapCNS();
    void set_kntrlCNS();

signals:
    void sgnCmmy (const QString);
};

#endif // MKN_CINSI_H

