#ifndef HC_H
#define HC_H

//#include "globals.h"
#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QItemSelectionModel>
#include <QLabel>
#include <QPushButton>
#include <QDataWidgetMapper>
#include <QTableView>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QCheckBox>


// /// hC_ bana ait tüm sınıflar

/// sınıf listei
/// 1- hC_              - lib
/// 2- hC_Rs            - etiket üzerine diskten resim ekler,
///                       resmi değiştirir, pencerede gösterir
/// 3- hC_Tv            - menu eklenmiş tableview
/// 4- hC_Le            - sağda pushbutton olan lineedit
/// 4- hC_Te            - sağda pushbutton olan textedit
/// 5- hC_Tm            - QSqlRelationalTableModel
/// 6- hC_Gz            - tarihi gizler ve açar
/// 7- hC_Nr            - tableview da yeni eklenen kaydı bul

namespace HC_ {
class hC_Rs;
class hC_Tv;
class hC_Le;
class hC_Te;
class hC_Tm;
class hC_Gz;
class hC_Nr;
class hC_ArrD;
}
// forward declaration

class hC_Rs;
class hC_Tv;
class hC_Le;
class hC_Te;
class hC_Tm;
class hC_Gz;
class hC_Nr;


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

    explicit hC_Tv(QSqlRelationalTableModel *tb_model,
                   QDataWidgetMapper *tb_mapper,
                   QWidget *wdgt = nullptr );
    ~hC_Tv();

    QTableView  * table;
    QCheckBox   * cB_map;
    QPushButton * pB_ekle   ;
    QPushButton * pB_eklersm;
    QPushButton * pB_grscks;

    QPushButton *pB_sil;

    QPushButton *pB_ilk  ;
    QPushButton *pB_ncki ;
    QPushButton *pB_snrki;
    QPushButton *pB_son  ;

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
       QPushButton *pushButton2;
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




template <typename T> class  hC_Arr2D
{
public:
    hC_Arr2D(int n, int m)
    {
        _n = n;
        _array = new T*[n];
        for(int i = 0; i < n; i++)
            _array[i]= new T[m];

    }
    void setValue(int n, int m, T v){_array[n][m]=v;}
    T getValue(int n, int m){return _array[n][m];}
    ~hC_Arr2D(){
        for(int i=0; i < _n;i++)
            delete [] _array[i];
        delete [] _array;
    }

private:
    T **_array;
    int _n;

};

/// 2D array
///
/// ilk parametre arrayın boyunu gösterir
/// 2.boyut 3 adet sabittir
/// 2-3-4. parametreler QString leri alır

class  hC_ArrD
{
public:
    hC_ArrD(int n, int m )
    {
        _n = n;
        _array = new QString* [n];
        for(int i = 0; i < n; i++)
            _array[i]= new QString [m];
    }

    void setValue(int n, QString s1 = " ", QString s2 =" ", QString s3 = " ", QString s4="1")
    {
        _array[n][0]=s1;
        _array[n][1]=s2;
        _array[n][2]=s3;
        _array[n][3]=s4;
    }

    QString value(int n, int m)
    {
        return _array[n][m];
    }

    int length()
    {
        return _n ;
    }

    ~hC_ArrD(){
        for(int i=0; i < _n;i++)
            delete [] _array[i];
        delete [] _array;
    }

private:
    QString **_array;
    int _n;

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
                     hC_ArrD *);
     ~hC_Rm();
     // QSqlRelationalTableModel *model(QSqlRelationalTableModel *model);
     //QSqlRelationalTableModel  *hC_rm;
};



class hC_Gz
{
public:

    hC_Gz(QDateTimeEdit *tarih, QString vsbl);
};


class hC_Nr
{
public:
    explicit hC_Nr(hC_Tv *searchingTable, int aranan, int kolon);

private:
    QModelIndex hC_NrSetCurrentIndex(QModelIndex Index);
};


//////////////////////////////////////////////////////////
/// \brief hC_tBcreator::hC_tBcreator
///
///   create table and others




//#include "clsn.h"

class hC_tBcreator : public QWidget
{
    Q_OBJECT
public:
    explicit hC_tBcreator( );

    /*QString *tb_name,
                          hC_ArrD *tb_flds,
                          QString *tb_ndex,
                          QSqlRelationalTableModel *tb_modl,
                          hC_Tv *tb_view,
                          QDataWidgetMapper *tb_mapper,
                          QList<QWidget*> *win_wdgts );
*/
    ~hC_tBcreator();

    QString create(hC_ArrD *tb_flds);

    void model(hC_ArrD *tb_flds, QList<QWidget *> *tb_wdgts);

    void    view(hC_ArrD *tb_flds, QList<QWidget *> *tb_wdgts);

    void    map(hC_ArrD *tb_flds, QList<QWidget *> *tb_wdgts);

private:
    QString     _mesaj;

public:
    /////////////////////////////////////////////////
        hC_Tv                    * tb_view     {} ;
        QSqlRelationalTableModel * tb_model     {} ;
        QItemSelectionModel      * tb_slctnMdl {} ;
        QDataWidgetMapper        * tb_mapper   {} ;

        QString                  * tb_name     {} ;

        QString                  * tb_ndex     {} ;
        QWidget                  * win_Wdgt  {} ;
        QLabel                   * win_Label {} ;
        QLabel                   * win_Rsm   {} ;
    /////////////////////////////////////////////////

};


#endif // HC__H
