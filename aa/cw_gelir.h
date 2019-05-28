#ifndef CW_GELIR_H
#define CW_GELIR_H

#include "globals.h"

namespace Ui {
class CW_gelir;
}

class CW_gelir : public QWidget
{
    Q_OBJECT

public:
    explicit CW_gelir(QWidget *parent = 0);
    ~CW_gelir();

private:
    void setupModel();
    void createUI();

    QDataWidgetMapper *map_gelir{};
    QSqlTableModel    *model{};
    QTableView     *tV_gelir{};



    private slots:

    void on_pB_EK_clicked();
    void on_pB_SL_clicked();
    //void on_pB_RP_clicked();
    //void resim(QModelIndex);

    void on_chbx_detay_stateChanged();
};

#endif // CW_GELIR_H
