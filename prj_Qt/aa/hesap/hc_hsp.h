#ifndef hC_HSP_H
#define hC_HSP_H

#include "main/globals.h"
namespace nSHsp
{
class hC_HSP;
}
class hC_HSP : public hC_tBcreator
{
    Q_OBJECT
public:
    explicit hC_HSP();
    ~hC_HSP();

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
    QModelIndex newIndex;

    void tbsetup () ;

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

#endif // hC_HSP_H
