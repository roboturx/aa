#ifndef WW_MKCINS_H
#define WW_MKCINS_H

#include "globals.h"


namespace Ui {
    class WW_Mkcins;
}

class WW_Mkcins : public QWidget
{
	Q_OBJECT

    public:
    explicit WW_Mkcins(QWidget *parent = 0);
	~WW_Mkcins();

    QTableView *tv_mkcins;
    QTableView *tv_mkmark;
    QTableView *tv_mkmodl;

    QPushButton *pb_eklE_cns ;
    QPushButton *pb_sil_cns ;
    QPushButton *pb_eklE_mrk ;
    QPushButton *pb_sil_mrk ;
    QPushButton *pb_eklE_mdl ;
    QPushButton *pb_sil_mdl ;
    QPushButton *pb_tmm ;

    QSqlRelationalTableModel *mdl_mkcins ;
    QSqlRelationalTableModel *mdl_mkmark ;
    QSqlTableModel *mdl_mkmodl ;

    QWidget *pnc;


    private slots:
    void onpb_tmm_clicked();
    void onpb_eklE_cns_clicked();
    void onpb_sil_cns_clicked();
    void onpb_eklE_mrk_clicked();
    void onpb_sil_mrk_clicked();
    void onpb_eklE_mdl_clicked();
    void onpb_sil_mdl_clicked();

    void ontV_cins_filterSLOT(QModelIndex);
    void ontV_mark_filterSLOT(QModelIndex);
    void ontv_cns_clicked();
    void ontv_mrk_clicked();


    private:

    void cr_ui();
    void cr_mdl_mkcins();
    void cr_mdl_mkmark();
    void cr_mdl_mkmodl();
    void cr_kontrol();
};

#endif // WW_MKCINS_H
