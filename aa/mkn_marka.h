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


    QString sgnText{};

    void mkmark_setup();
    QString mkmark_VTd();
    void mkmark_model(QSqlRelationalTableModel *model);

    QLabel *lB_rsm;
    //DBase *dbase;
    hC_Tv             *MRKtview{};
    QSqlRelationalTableModel *MRKmodel{} ;
    QItemSelectionModel      *MRKslctnMdl;
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
