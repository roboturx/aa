#ifndef HC_HSPADD_H
#define HC_HSPADD_H

#include "libs/globals.h"
#include "main/taskitem.h"

class hC_hspAdd : public QMainWindow
{
    Q_OBJECT
public:
    explicit hC_hspAdd(QWidget *parent = nullptr);
    ~hC_hspAdd();
    QWidget *mainwdgt ;


    TaskItem* yeni() { return yeniItem; };

    QLineEdit* le_ad ;
    QLineEdit* le_acklama ;
    QComboBox* cb_topluHesap;
    QComboBox* cb_hesapTuru ;
    QComboBox* cb_ustHesap ;

private:
    TaskItem *yeniItem;
    QString f_ms_hesapAd;
    QString f_ms_hesapAcklm;
    bool    f_mb_topluHesap;
    QString f_ms_hesapTuru;
    QString f_ms_ustHesap;
    QString f_ms_DBFile;


private slots:
    void yaz();


signals:

};

#endif // HC_HSPADD_H
