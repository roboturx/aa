#ifndef CW_FTR_H
#define CW_FTR_H


#include "globals.h"

namespace nSFtr {
class hC_FTR;
}

class hC_FTR : public QWidget
{
    Q_OBJECT

public:

    void    ftr_setup () ;
    QString ftr_VTd   () ;
    void    ftr_model () ;


    hC_Tv                    * FTRtview   {} ;
    QSqlRelationalTableModel * FTRmodel   {} ;
    QItemSelectionModel      * FTRslctMdl {} ;
    QDataWidgetMapper        * FTRmapper  {} ;

    QWidget * ftrWdgt {} ;
    QLabel  * lB_ftr     {} ;
    QLabel  * lB_ftrrsm  {} ;

    QLabel      *lB_brkd{} ;
    QLineEdit   *lE_faturano{}  ;
    hC_Le   *lE_firma{} ;
    QLineEdit   *lE_tarih{};
    QLineEdit   *lE_aciklama{};


private:
    void ftr_ui () ;
    void ftr_wdgt  () ;
    void ftr_view  () ;
    void ftr_map   () ;
    void ftr_kntrl () ;


signals:
    void sgnFtr (const QString* sgnKod,
                     const QString* sgnBarkod,
                     const QString* sgnMalzeme,
                     const QString* sgnBirim
                     ); // ftr bilgisi yayınla

    // depo detay

    void    ftrdet_setup();
    QString ftrdet_VTd();
    void    ftrdet_model(QSqlRelationalTableModel * );


    hC_Tv             *FTRDETtview{};
    QSqlRelationalTableModel *FTRDETmodel{} ;
    QItemSelectionModel      *FTRDETselectionMdl{} ;
    QDataWidgetMapper        *FTRDETmapper{} ;

    QWidget     *wdgt_mapFTR_dty{};

    QLabel      *lB_FTRdet{}  ;
    QLineEdit   *lE_mlzdetbarkod{}  ;
    QLineEdit   *lE_mlzm{} ;
    hC_Le       *lE_mlzdetmlzm{} ;
    QLineEdit   *lE_mlzdetaciklama{}  ;
    QLineEdit   *lE_mlzdettarih{} ;
    QLineEdit   *lE_mlzdetgc{} ;
    QLineEdit   *lE_mlzdetgcno{} ;
    QLineEdit   *lE_mlzdetmiktar{}  ;
    QLineEdit   *lE_mlzdetbirim{}  ;
    QLineEdit   *lE_mlzdetfiyat{}   ;
    QLineEdit   *lE_mlzdetkdv{}  ;
    QLineEdit   *lE_ftrToplam;
    QLineEdit   *lE_ftrKdv;
    QLineEdit   *lE_ftrGenelToplam;



    private:
    void wd_FTRdet()        ;
    void setup_viewFtrDet() ;
    void setup_modelFtrDet();
    void setup_mapFtrDet()  ;
    void setup_kntrlFtrDet();

private slots:
    void slt_ftr_hesap();

protected:
    void showEvent(QShowEvent *);

public:
    explicit hC_FTR(QWidget *parent = nullptr);
    ~hC_FTR() ;

};



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



#endif // CW_FTR_H
