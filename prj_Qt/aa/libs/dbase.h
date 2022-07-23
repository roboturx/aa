#ifndef DBASE_H
#define DBASE_H

#include "globals.h"
#ifdef CLSN
#include "clsn.h"

#endif



namespace Ui
{
class DBase;
}

class DBase : public QWidget
{
    Q_OBJECT

public:
    explicit DBase(QWidget* parent = 0);
    ~DBase();
    bool setupDBase();
    void yaz(const QString& z);

    QTextEdit* durum;
    QWidget* win_Wdgt;
private:

    void dbwdgt  () ;
    void dbui    () ;
    void dbkntrl () ;

    //    Ui::DBase *ui;

    // veritabanı yoksa oluştur, bağlan
    void VTDosyaKontrol();

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
