#ifndef MN_NAVI_H
#define MN_NAVI_H

#include "globals.h"

namespace Ui {
class HC_TableView;
}


class HC_TableView : public QTableView
{    Q_OBJECT

public:
    explicit HC_TableView(int &renk, QTableView *parent = 0);
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
