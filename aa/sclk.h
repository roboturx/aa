#ifndef SCLK_H
#define SCLK_H

#include <globals.h>
#include "hc_.h"

namespace ns_SCLK {
class hC_SCLK;
}

class hC_SCLK : public QWidget
{
    Q_OBJECT

public:
    explicit hC_SCLK(QWidget *parent = nullptr);
    ~hC_SCLK();

public:

    void    sclk_setup();
    QString sclk_VTd();
    void    sclk_model(QSqlRelationalTableModel * );

    hC_Tv*                    SCLKtview;
    QSqlRelationalTableModel* SCLKmodel{};
    QItemSelectionModel*      SCLKselectionMdl;
    QDataWidgetMapper*        SCLKmapper;

private:
    void sclk_ui()   ;
    void sclk_view() ;
    void sclk_map()  ;
    void sclk_kntrl();


public slots:
   void clk_SCbosh();

private slots:
    void onmnIEDET_SCekle();
    void rowChanged_ISCILIK(QModelIndex);
    void rightMenu_ISCILIK(QPoint pos);
    void SCekle();
    void sil_ISCILIK();
    void ayar_ISCILIK();

public:
    // SC variable
    QLabel *lB_sclk ;
    QLabel *lB_rsm ;

    QLineEdit *lE_SCno{};
    QDateTimeEdit *dE_SCtarih{};
    QComboBox *cbx_SCbirim{};
    QComboBox *cbx_SCusta{};
    QLineEdit *lE_SCsaat{};
    QLineEdit *lE_SCucret{};
    QComboBox *cbx_SCucrettip{};
    QLineEdit *lE_SCaciklama{};
    QString *SCdet_idno{};
    QString *SCdetno{};
    QString *SCno{};

    QGridLayout *gL{};
    QGridLayout *gLdet{};
    QHBoxLayout *hL1{} ;
    QHBoxLayout *hL2{} ;
    QPushButton *pB1{} ;
    QPushButton *pB2{} ;
    QPushButton *pB3{} ;
    QPushButton *pB4{} ;
    QPushButton *pB5{} ;
    QPushButton *pB6{} ;
    QPushButton *pB7{} ;



};


#endif // SCLK_H
