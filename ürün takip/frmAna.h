#ifndef frmAna_H
#define frmAna_H

#include <QMainWindow>
#include "frmUrun.h"
#include "frmGrs.h"
#include <QSqlQueryModel>

namespace Ui {
class frmAna;
}

class frmAna : public QMainWindow
{
    Q_OBJECT

private:
    frmUrun *m_frmUrun;
    frmGrs *m_frmGrs;

public:
    explicit frmAna(QWidget *parent = 0);
    ~frmAna();
    void LoadProducts();

private slots:

    void loginOKWith(QString name);
    void showMenuAbout();
    void quitApp();
    void on_btnRefresh_clicked();
    void on_btnProductOperations_clicked();
    void on_tblProducts_activated(const QModelIndex &index);
    void on_tblProducts_pressed(const QModelIndex &index);
    void on_btnSearch_clicked();
    void on_btnSearchReset_clicked();
    void on_btnClear_clicked();
    void on_cbSearchByBarkod_stateChanged(int arg1);
    void on_cbSearchByName_stateChanged(int arg1);
    void on_cbSearchByDate_stateChanged(int arg1);
    void on_cbSearchByQuantity_stateChanged(int arg1);
    void on_cbSearchByPrice_stateChanged(int arg1);
    void on_cbSearchByDateAdd_stateChanged(int arg1);
    void on_cbSearchByDateUpdate_stateChanged(int arg1);
    void on_cbSearchByPricePurchase_stateChanged(int arg1);
    void on_cbSearchByPriceSale_stateChanged(int arg1);

private:
    Ui::frmAna *ui;
    void LoadProductInfoToLabel(const QModelIndex &index);
    void closeEvent (QCloseEvent *event);

};

#endif // frmAna_H
