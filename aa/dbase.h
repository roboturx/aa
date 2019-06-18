#ifndef DBASE_H
#define DBASE_H

#include "globals.h"
#include "hc_.h"

namespace Ui {
class DBase;
}

class DBase : public QWidget
{
    Q_OBJECT

public:
    explicit DBase(QWidget *parent = nullptr);
    ~DBase();

    void modelCalisan(QSqlRelationalTableModel *model);
    QString *CLSNtableName{};

    void modelMeslek(QSqlRelationalTableModel *model);
    QString *MSLKtableName{};

    void modelFatura(QSqlRelationalTableModel *model);
    QString *FTRtableName{};

    void modelMalzeme(QSqlRelationalTableModel *model);
    QString *MLZMtableName{};

    void modelMalzemeDetay(QSqlRelationalTableModel *model);
    QString *MLZDETtableName{};

    void modelFirma(QSqlRelationalTableModel *model);
    QString *FRMtableName{};

    void modelMakina(QSqlRelationalTableModel *model);
    QString *MKNtableName{};

    void modelCinsi(QSqlRelationalTableModel *model);
    QString *CNStableName{};

    void modelMarka(QSqlRelationalTableModel *model);
    QString *MRKtableName{};

    void modelModeli(QSqlRelationalTableModel *model);
    QString *MDLtableName{};



    bool setupDBase();
    void yaz(const QString& z);
    //    QTextEdit *durum;
private:
    Ui::DBase *ui;


    //    void dbcontrol();
    // veritabanı yoksa oluştur, bağlan
    void VTDosyaKontrol();

    QString VTd_CLSN();
    QString VTd_MSLK();

    QString VTd_FRMA();
    QString VTd_FTRA();
    QString VTd_Mlzm ();
    QString VTd_MlzmDETAY();

    QString VTd_mkn ();
    QString VTd_CINS ();
    QString VTd_MARKA ();
    QString VTd_MODEL ();


    void VTd_ISEMRI ();
    void VTd_ISEMRIDETAY ();
    void VTd_IEDTAMIRYERI ();
    void VTd_IEDTYDETAY ();
    void VTd_ISCILIK ();
    void VTd_TASINIR () ;

    void VTd_MKYAG ();
    void VTd_MKFILTRE ();
    void VTd_MKAKU ();
    void VTd_MKLASTIK ();
    void VTd_MKMUAYENE ();
    void VTd_MKSIGORTA ();
    void VTd_MKYAKIT ();
    void VTd_MKANTIFIRIZ ();
    void VTd_MKZINCIR ();
    void VTd_MKHGS ();

};

#endif // DBASE_H
