#ifndef hC_HSPDTY_H
#define hC_HSPDTY_H

#include "libs/globals.h"
//#include "hc_tree.h"

namespace nSHsp
{
class hC_HSPDTY;
}
class hC_HSPDTY : public hC_tBcreator
{
    Q_OBJECT
public:
    explicit hC_HSPDTY();
    ~hC_HSPDTY();

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QLineEdit   *lE_pid=nullptr    ;
    QLineEdit   *lE_ad=nullptr    ;

    QDateEdit   *dE_tarih=nullptr   ;
    QLineEdit   *lE_aciklama{};
    QComboBox   *cB_parabrm=nullptr;
    QLineEdit   *lE_not{};
    QLineEdit   *lE_gizli{};
    QLineEdit   *lE_toplu{}   ;
    QComboBox   *cB_turu{}   ;
    QLineEdit   *lE_lft{}   ;
    QLineEdit   *lE_rgt{}   ;
    QGridLayout* win_Grid;
    int hesapID{};
    int hesapParentID{};
    QString hesapAd{};
    int hesapLeft{};
    int hesapRight{};
    int reccount{};
    QModelIndex curIndex;

    void tbsetup () ;


   // hC_tree *tb_treeview;


private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;
    void debugger(QString num) ;

protected:
    void showEvent(QShowEvent *);

//signals:
//    void sgnHsp (const QString sgnHspID); //




private slots:

    void slt_tbx_rowChange(); //connect selectionmodel change
};

#endif // hC_HSPDTY_H
