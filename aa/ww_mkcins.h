#ifndef WW_MKCINS_H
#define WW_MKCINS_H

#include "globals.h"
#include "hc_tableview.h"
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


    QString sgnText;
    void setup_CNS();
    DBase *dbase;

    QLabel *lB_rsm;
    HC_TableView             *CNStview{};
    QSqlRelationalTableModel *CNSmodel{} ;
    QItemSelectionModel      *CNSselectionMdl;
    QDataWidgetMapper        *CNSmapper;


    QLabel *lB_rsm1;
    HC_TableView             *MRKtview{};
    QSqlRelationalTableModel *MRKmodel{} ;
    QItemSelectionModel      *MRKselectionMdl;
    QDataWidgetMapper        *MRKmapper;

    QLabel *lB_rsm2;
    HC_TableView             *MDLtview{};
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
    void sgnCmmy (const QString sgnCmmy);

};

#endif // WW_MKCINS_H
