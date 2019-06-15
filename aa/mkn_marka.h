#ifndef MKN_MARKA_H
#define MKN_MARKA_H

#include "globals.h"
#include "hc_.h"
#include "dbase.h"
namespace Ui {
    class Mkn_Marka;
}

class Mkn_Marka : public QDialog
{
    Q_OBJECT

public:
    explicit Mkn_Marka(QDialog *parent = nullptr);
    ~Mkn_Marka();


    QString sgnText{};
    void setup_CNS();
    DBase *dbase;

    QLabel *lB_rsm;

    hC_Tv             *MRKtview{};
    QSqlRelationalTableModel *MRKmodel{} ;
    QItemSelectionModel      *MRKselectionMdl;
    QDataWidgetMapper        *MRKmapper;

private:

    void set_uiMRK();

    void set_modelMRK();
    void set_viewMRK();
    void set_mapMRK();
    void set_kntrlMRK();

signals:
    void sgnCmmy (const QString);
};

#endif // MKN_MARKA_H
