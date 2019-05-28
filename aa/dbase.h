#ifndef DBASE_H
#define DBASE_H

#include "globals.h"

namespace Ui {
class DBase;
}

class DBase : public QWidget
{
    Q_OBJECT

public:
    explicit DBase(QWidget *parent = nullptr);
    ~DBase();

    QSqlRelationalTableModel *mdlFtr;
    QSqlRelationalTableModel *modelFatura();
    QSqlRelationalTableModel *mdlMlzm;
    QSqlRelationalTableModel *modelMalzeme();
    QSqlRelationalTableModel *mdlMlzmDty;
    QSqlRelationalTableModel *modelMalzemeDetay();
    bool setupDBase();
    void yaz(QString z);
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




        void VTd_mkn ();
        void VTd_CINS ();
        void VTd_MARKA ();
        void VTd_MODEL ();


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
