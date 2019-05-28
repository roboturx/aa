#ifndef CW_GRS_H
#define CW_GRS_H


#include <globals.h>


namespace Ui {
class Cw_Grs;
}

class Cw_Grs : public QWidget
{
    Q_OBJECT

public:
    explicit Cw_Grs(QWidget *parent = 0);
    ~Cw_Grs() = default;

    //bool setData(const QModelIndex & index,
    //             const QVariant & value,
      //           int role);

public:

    QSqlRelationalTableModel *model_spre{};
    QSqlTableModel *model_spreDet{};
    QTableView *tV_spre{} ;
    QTableView *tV_spredet{} ;

    QPushButton *pb_ieo{} ;
    QPushButton *pb_se_sil{} ;
    QPushButton *pb_se_yaz{} ;
    QPushButton *pb_se_{} ;
    QPushButton *pb_sedet_ekle{} ;
    QPushButton *pb_sedet_sil{} ;
    QPushButton *pb_sedet_{} ;

    QLabel *lbl_mkn{};
    QLabel *lbl_spre{};



private:

    void setup_VTdGrs();
    void VTd_SIPARISEMRI ();
    void VTd_SIPARISEMRIDETAY ();

    void cr_spre_ui();
    void cr_spre_model();
    void cr_spre_view();
    void cr_spredet_model();
    void cr_spredet_view();
    void cr_spre_kontrol();


private slots:

    void ontV_spre_row_changed(QModelIndex);
    void onpb_spreSil();
    void onpb_spreYaz();
    void onpb_spreEkleDDD();
    void onpb_spreDetayEkle();
    void onpb_spreDetaySil();
    void onpb_spreDetayEkleDDD();
    void onpb_is_emri_olustur();

};

#endif // CW_GRS_H
