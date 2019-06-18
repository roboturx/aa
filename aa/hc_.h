﻿#ifndef HC_H
#define HC_H

#include "globals.h"

// /// hC_ bana ait tüm sınıflar

/// sınıf listei
/// 1- hC_              - lib
/// 2- hC_Rs            - etiket üzerine diskten resim ekler,
///                       resmi değiştirir, pencerede gösterir
/// 3- hC_Tv            - menu eklenmiş tableview
/// 4- hC_Le            - sağda pushbutton olan lineedit
/// 4- hC_Te            - sağda pushbutton olan textedit
/// 5- hC_Tm            - QSqlRelationalTableModel


namespace HC_ {
class hC_Rs;
class hC_Tv;
class hC_Le;
class hC_Te;

}
// forward declaration

class hC_Rs;
class hC_Tv;
class hC_Le;
class hC_Te;



class hC_
{
public:
    hC_();
};



// ////////////////////////////////////////////
/// \brief The Resim class
///
///   Resim class parametreleri
///   1- label           - public tanımlanan label
///   2- view            - table a ait view
///   3- model           - table a ait model
///   4- selection model - table a ait s model
///   5- field           - table da field ismi
///   6- işlem türü      - class ne yapacak
///
///   ilk parametre ile class a yollanan label üzerinde
///   son parametre ile belirlenen işlem yapılır
///
///   son parametre işlevleri
///   "ekle"      - label da gösterilecek resmin disk üzerinden
///               seçilmesini sağlar ve modeldeki fielda
///               kayıt eder.
///               * Tüm parametreler dolu olmalıdır
///
///   "değiştir"   -  row change bağlı çalışır,
///               table dan field içeriğini alır. Field
///               içeriği boşsa label da "resim yok"
///               resmini gösterir.
///               field da resim dosyası varsa resmin
///               içeriğini labelda gösterir
///               * Tüm parametreler dolu olmalıdır
///
///   ""          -  Gelen label da gözüken resmin,
///               resmin üzerinde sağ tıklanması
///               sonucunda bir pencerede büyültülerek
///               gösterilmesini sağlar.
///               *Sadece ilk parametrede label gönderilmesi
///               yeterlidir.


class hC_Rs : public QWidget
{
    Q_OBJECT

public:

    explicit hC_Rs ( QLabel *rsm_updResim= nullptr,
            hC_Tv *rsm_table= nullptr,
            QSqlRelationalTableModel *rsm_model= nullptr,
            QItemSelectionModel *rsm_selectionModel= nullptr,
            QString rsm_field= nullptr,
            QString rsm_new_upd = nullptr);

};



// /////////////////////////////////////////////////////////////////////////////////


//    T A B L E V I E W   -----> hC_Tv


// /////////////////////////////////////////////////////////////////////////////////


class hC_Tv : public QWidget
{
    Q_OBJECT

public:

    explicit hC_Tv(int renk=1, QWidget *parent = nullptr);
    ~hC_Tv();
    QTableView *table;
    QPushButton *pB_ekle   ;
    QPushButton *pB_eklersm;
    QPushButton *pB_grscks;

    QPushButton *pB_sil;

    QPushButton *pB_ilk  ;
    QPushButton *pB_ncki ;
    QPushButton *pB_snrki;
    QPushButton *pB_son  ;
    /*
     public slots:
         void SLT_ekle();
         void SLT_eklersm();
         void SLT_grscks();
         void SLT_sil();

         void SLT_first();
         void SLT_next();
         void SLT_previous();
         void SLT_last();




     signals:
          void sG_ekle();
          void sG_eklersm();
          void sG_grscks();
          void sG_sil();

          void sG_first();
          void sG_next();
          void sG_previous();
          void sG_last();

     */

};




// /////////////////////////////////////////////////////////////////////////////////


//    L I N E D I T    -----> HC_LE

// Sağ tuş butonu olan lineedit
// /////////////////////////////////////////////////////////////////////////////////


class hC_Le : public QWidget
{    Q_OBJECT

 public:
     explicit hC_Le(QWidget *parent = nullptr);
     ~hC_Le();
     QLineEdit  *lineEdit;
      QPushButton *pushButton;
};



// /////////////////////////////////////////////////////////////////////////////////


//    TEXT E D I T    -----> hC_textEdit

// Sağda push butonu olan textedit
// /////////////////////////////////////////////////////////////////////////////////


class hC_Te : public QWidget
{    Q_OBJECT

 public:
     explicit hC_Te(QWidget *parent = nullptr);
     ~hC_Te();
     QTextEdit  *hC_txEdt;
      QPushButton *hC_txEdtpB;
};





// /////////////////////////////////////////////////////////////////////////////////


//    QSQLRELATIONATABLEMODEL    -----> hC_Rm

// rel model
// /////////////////////////////////////////////////////////////////////////////////


class hC_Rm : public QSqlRelationalTableModel
{    Q_OBJECT

 public:
     explicit hC_Rm (QString *rm_Table,
           QSqlRelationalTableModel *rm_model,
           QString *rm_IndexField,
           QStringList *rm_List);
     ~hC_Rm();
    // QSqlRelationalTableModel *model(QSqlRelationalTableModel *model);
     //QSqlRelationalTableModel  *hC_rm;
};




#endif // HC__H