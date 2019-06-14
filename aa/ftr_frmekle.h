#ifndef FTR_FRMEKLE_H
#define FTR_FRMEKLE_H

#include <QtWidgets>
#include "cw_fr.h"
#include "cw_mlzm.h"

namespace Ui {
class Ftr_FrmEkle;
class FtrDet_MlzEkle;
class Resim;
}


class Resim : public QWidget
{
    Q_OBJECT

public:

    Resim(QWidget *wD_resim=nullptr, QWidget *parent = nullptr);

    QByteArray resimEkle();
    void resimUpdate(QWidget *rsm_updResim,
                       HC_TableView *rsm_table,
                       QSqlRelationalTableModel *rsm_model,
                       QItemSelectionModel *rsm_selectionModel,
                       QString rsm_field,
                       QString rsm_new_upd = nullptr);


};


class wD_Rsm : public QWidget
{
    Q_OBJECT

public:

    wD_Rsm(QString *png_name = nullptr,
           QLabel *wD_resim  = nullptr,
           QWidget *parent   = nullptr);

};



// //////////////////////////////////////////// faturaya firma ekle
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
    Cw_Mlzm  *malzeme;
protected:
    void reject() ;
private:
    QString m_malzeme;
    void setMalzeme(const QString &value);
};




#endif // FTR_FRMEKLE_H
