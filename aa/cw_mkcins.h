#ifndef WW_MKCINS_H
#define WW_MKCINS_H

#include "globals.h"
#include "hc_.h"
#include "dbase.h"
namespace Ui {
    class WW_Mkcins;
}

class WW_Mkcins : public QDialog
{
	Q_OBJECT

public:
    explicit WW_Mkcins(QDialog *parent = nullptr);
	~WW_Mkcins();


    QString sgnText1{}, sgnText2{}, sgnText3{} ;
    void setup_CNS();
    DBase *dbase;

    QLabel *lB_rsm;
    hC_Tv             *CNStview{};
    QSqlRelationalTableModel *CNSmodel{} ;
    QItemSelectionModel      *CNSselectionMdl;
    QDataWidgetMapper        *CNSmapper;


    QLabel *lB_rsm1;
    hC_Tv             *MRKtview{};
    QSqlRelationalTableModel *MRKmodel{} ;
    QItemSelectionModel      *MRKselectionMdl;
    QDataWidgetMapper        *MRKmapper;

    QLabel *lB_rsm2;
    hC_Tv             *MDLtview{};
    QSqlRelationalTableModel *MDLmodel{} ;
    QItemSelectionModel      *MDLselectionMdl;
    QDataWidgetMapper        *MDLmapper;

private:

    void set_uiCNS();

    void set_modelCNS();
    void set_viewCNS();
    void set_mapCNS();
    void set_kntrlCNS();

    void set_modelMRK();
    void set_viewMRK();
    void set_mapMRK();
    void set_kntrlMRK();

    void set_modelMDL();
    void set_viewMDL();
    void set_mapMDL();
    void set_kntrlMDL();



signals:
    void sgnCmmy (const QString, const QString, const QString);
};

#endif // WW_MKCINS_H
