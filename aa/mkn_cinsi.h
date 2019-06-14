#ifndef MKN_CINSI_H
#define MKN_CINSI_H


#include "globals.h"
#include "hc_tableview.h"
#include "dbase.h"
namespace Ui {
    class Mkn_Cinsi;
}

class Mkn_Cinsi : public QDialog
{
    Q_OBJECT

public:
    explicit Mkn_Cinsi(QDialog *parent = nullptr);
    ~Mkn_Cinsi();


    QString sgnText ;
    void setup_CNS();
    DBase *dbase;

    QLabel *lB_rsm;
    HC_TableView             *CNStview{};
    QSqlRelationalTableModel *CNSmodel{} ;
    QItemSelectionModel      *CNSselectionMdl;
    QDataWidgetMapper        *CNSmapper;

private:

    void set_uiCNS();

    void set_modelCNS();
    void set_viewCNS();
    void set_mapCNS();
    void set_kntrlCNS();

signals:
    void sgnCmmy (const QString);
};

#endif // MKN_CINSI_H

