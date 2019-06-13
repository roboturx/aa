#ifndef MN_NAVI_H
#define MN_NAVI_H

#include "globals.h"

namespace Ui {
class HC_;
}


// /////////////////////////////////////////////////////////////////////////////////


//    TEXT E D I T    -----> hC_textEdit

// Sağ tuş butonu olan textedit
// /////////////////////////////////////////////////////////////////////////////////


class hC_textEdit : public QWidget
{    Q_OBJECT

 public:
     explicit hC_textEdit(QWidget *parent = nullptr);
     ~hC_textEdit();
     QTextEdit  *hC_txEdt;
     QPushButton *hC_txEdtpB;
};




// /////////////////////////////////////////////////////////////////////////////////


//    L I N E D I T    -----> HC_LE

// Sağ tuş butonu olan lineedit
// /////////////////////////////////////////////////////////////////////////////////


class HC_LE : public QWidget
{    Q_OBJECT

 public:
     explicit HC_LE(QWidget *parent = nullptr);
     ~HC_LE();
     QLineEdit  *lineEdit;
     QPushButton *pushButton;
};







// /////////////////////////////////////////////////////////////////////////////////


//    T A B L E V I E W   -----> HC_TableView


// /////////////////////////////////////////////////////////////////////////////////


class HC_TableView : public QWidget
{    Q_OBJECT

 public:

     explicit HC_TableView(int renk=1, QWidget *parent = nullptr);
     ~HC_TableView();

     QTableView  *table;
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


#endif // MN_NAVI_H
