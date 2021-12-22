#ifndef DBASE_H
#define DBASE_H

#include <QWidget>

#include "adrs/clsn.h"
#include "adrs/frm.h"
#include "adrs/ftr.h"

#include "main/globals.h"
#include "main/dbase.h"

#include "mchn/mkn.h"
#include "mchn/mkn_cinsi.h"
#include "mchn/mkn_marka.h"
#include "mchn/mkn_modeli.h"
#include "mlzm/mlzm.h"
#include "mlzm/mlzm_gc.h"

#include "ie/ie.h"
#include "ie/iedet.h"
#include "ie/sclk.h"
#include "ie/tsnr.h"

#include "kira/kira.h"



namespace Ui
{
    class DBase;
}

class DBase : public QWidget
{    Q_OBJECT

public:
    explicit DBase(QWidget *parent = nullptr);
    ~DBase();
    bool setupDBase();
    void yaz(const QString& z);
private:
    Ui::DBase *ui;

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
