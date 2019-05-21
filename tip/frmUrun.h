

#ifndef frmUrun_H
#define frmUrun_H

#include <QDialog>

namespace Ui {
class frmUrun;
}

class frmUrun : public QDialog
{
    Q_OBJECT

public:
    explicit frmUrun(QWidget *parent = 0);
    ~frmUrun();

    void Clear();
    void LoadProduct(const int index);
    void DbProduct();


private:
    bool m_isReadonly;

    bool CheckInputs();
    void LoadProduct(const QString barcode);
    void LoadProductsToComboBox();

signals:
    void Refresh();


public slots:

    void on_btnAdd_clicked();

    void on_btnCopy_clicked();

    void on_btnUpdate_clicked();

    void on_btnDelete_clicked();

    void on_cbID_activated(int index);

    void on_cbReadonly_stateChanged(int arg1);

private:
    Ui::frmUrun *ui;
};

#endif // frmUrun_H
