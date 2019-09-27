#ifndef mkevrk_H
#define mkevrk_H

//#include <QWidget>
#include "globals.h"
//#include "mkn.h"
namespace nSMkn {
class _Evr;
}

class _Evr:public QWidget
{
    Q_OBJECT

public:
    explicit _Evr();
    ~_Evr();

private:

};


class  Evr_Sgrt : public QWidget
{
    Q_OBJECT

public:
    explicit  Evr_Sgrt();
    ~Evr_Sgrt();

private:
    void cr_Evr_Sgrt_ui();
    void cr_Evr_Sgrt_model();
    void cr_Evr_Sgrt_view();
    void cr_Evr_Sgrt_kontrol();

 private slots:
    void ontV_Evr_Sgrt_row_changed(QModelIndex);
    void onpb_Evr_Sgrt_Sil();
    void onpb_Evr_Sgrt_Yaz();
    void onpb_Evr_Sgrt_EkleDDD();
    void onpb_Evr_Sgrt_Ekle();

public:
    QSqlRelationalTableModel *mdl_evr_sgrt{};

    QTableView *tV_evr_sgrt{} ;

    QPushButton *pb_sgrt_ekle{} ;
    QPushButton *pb_sgrt_ekleDDD{} ;
    QPushButton *pb_sgrt_sil{} ;
    QPushButton *pb_sgrt_yaz{} ;
    QPushButton *pb_sgrt_DDD{} ;

};


class  Evr_Mua : public QWidget
{
    Q_OBJECT

public:
    explicit  Evr_Mua();
    ~Evr_Mua();

private:
    void cr_Evr_Mua_ui();
    void cr_Evr_Mua_model();
    void cr_Evr_Mua_view();
    void cr_Evr_Mua_kontrol();

private slots:
    void ontV_Evr_Mua_row_changed(QModelIndex);
    void onpb_Evr_Mua_Sil();
    void onpb_Evr_Mua_Yaz();
    void onpb_Evr_Mua_EkleDDD();
    void onpb_Evr_Mua_Ekle();

public:
    QSqlRelationalTableModel *mdl_evrk_mua{};
    QTableView *tV_evrk_mua{} ;

    QPushButton *pb_mua_ekle{} ;
    QPushButton *pb_mua_ekleDDD{} ;
    QPushButton *pb_mua_sil{} ;
    QPushButton *pb_mua_yaz{} ;
    QPushButton *pb_mua_DDD{} ;
};

#endif // mkevrk_H
