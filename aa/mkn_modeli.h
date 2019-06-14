#ifndef MKN_MODELI_H
#define MKN_MODELI_H

#include "globals.h"
#include "hc_tableview.h"
#include "dbase.h"
namespace Ui {
    class Mkn_Modeli;
}

class Mkn_Modeli : public QDialog
{
    Q_OBJECT

public:
    explicit Mkn_Modeli(QDialog *parent = nullptr);
    ~Mkn_Modeli();


    QString sgnText{};
    void setup_CNS();
    DBase *dbase;

    QLabel *lB_rsm;

    HC_TableView             *MDLtview{};
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
