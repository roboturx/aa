#ifndef FTR_FRMEKLE_H
#define FTR_FRMEKLE_H

#include <QtWidgets>
#include "cw_fr.h"

namespace Ui {
class Ftr_FrmEkle;
}

class Ftr_FrmEkle : public QDialog
{
    Q_OBJECT

public:
    explicit Ftr_FrmEkle(QDialog *parent = nullptr);
    ~Ftr_FrmEkle();


    QString getFirma() const;
    Cw_fr *firma;

protected:
    void reject() ;

private:
    Ui::Ftr_FrmEkle *ui;

    QString m_firma;
    void setFirma(const QString &value);

};


#endif // FTR_FRMEKLE_H
