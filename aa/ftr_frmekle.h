﻿#ifndef FTR_FRMEKLE_H
#define FTR_FRMEKLE_H

#include <QtWidgets>
#include "frm.h"
#include "mlzm.h"

namespace Ui {
class Ftr_FrmEkle;
class FtrDet_MlzEkle;
class Resim;
}


// //////////////////////////////////////////// faturaya firma ekle
class Ftr_FrmEkle : public QDialog
{
    Q_OBJECT

public:
    explicit Ftr_FrmEkle(QDialog *parent = nullptr);
    ~Ftr_FrmEkle();

    QString getFirma() const;
    hC_FRM *firma;
protected:
    void reject() ;
private:
    QString m_firma;
    void setFirma(const QString &value);
};


// ////////////////////////////////////////////// Fatura detaya malzeme ekle
class FtrDet_MlzEkle : public QDialog
{
    Q_OBJECT

public:
    explicit FtrDet_MlzEkle(QDialog *parent = nullptr);
    ~FtrDet_MlzEkle();

    QString getMalzeme() const;
    hC_MLZM  *malzeme;
protected:
    void reject() ;
private:
    QString m_malzeme;
    void setMalzeme(const QString &value);
};




#endif // FTR_FRMEKLE_H
