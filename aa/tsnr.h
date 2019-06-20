#ifndef TSNR_H
#define TSNR_H

#include <globals.h>
#include "hc_.h"


namespace ns_TSNR {
class hC_TSNR;
}

class hC_TSNR : public QWidget
{
    Q_OBJECT

public:
    explicit hC_TSNR(QWidget *parent = nullptr);
    ~hC_TSNR();

public:

    // TS    -  Taşınır

    void    tsnr_setup();
    QString tsnr_VTd();
    void    tsnr_model(QSqlRelationalTableModel * );

    hC_Tv*                    TSNRtview;
    QSqlRelationalTableModel* TSNRmodel{};
    QItemSelectionModel*      TSNRselectionMdl;
    QDataWidgetMapper*        TSNRmapper;


private:
    void tsnr_ui()   ;
    void tsnr_view() ;
    void tsnr_map()  ;
    void tsnr_kntrl();

public slots:
    void clk_TSbosh();

private slots:

    void onmnIEDET_TSekle();
    void rowChanged_TASINIR(QModelIndex);
    void rightMenu_TASINIR(QPoint pos);
    void TSekle();
    void sil_TASINIR();

public:

    // TS variable
    QComboBox *cbx_TSmlzm{};
    QSqlTableModel *cbxTSmlzmModel{} ;

    QLineEdit *lE_TSno{};
    QDateTimeEdit *dE_TStarih{};
    QComboBox *cbx_TSmalzeme{};
    QLineEdit *lE_TSmiktar{};
    QComboBox *cbx_TSbirim{};
    QLineEdit *lE_TSbfiyat{};
    QComboBox *cbx_TSdurum{};
    QLineEdit *lE_TSaciklama{};
    QString *TSdet_idno{};
    QString *TSdetno{};
    QString *TSno{};






};




#endif // TSNR_H
