#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include "globals.h"
#include "ie.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class DragWidget;
class CustomButton;
QT_END_NAMESPACE

//! [0]
class DragWidget : public QWidget
{
public:
    explicit DragWidget(QWidget *parent = nullptr);


    static int count;
    static int col;
    static int row;


private:
    void isEmriYeni(QPixmap *pixmap=nullptr,
                    QSqlRecord* record=nullptr);
    void isEmriListele();
    hC_IE* isEmri;
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;


};
//! [0]
//!
//!



class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = nullptr) ;
    ~CustomButton() override;

public:

    QLabel* resim;

    int getObjNo() const;
    void setObjNo(int value=0);

    QSqlRecord *getRecord() const;
    void setRecord(QSqlRecord *value=nullptr);

    QString getIeno() const;
    void setIeno(QString value=nullptr );

    QString getKurumno() const;
    void setKurumno(QString value=nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int objNo;

    QString No;

    QLabel* ieno;
    QLabel* kurumno;
    QSqlRecord* record;
    QPixmap* pixmap;
    QImage SimileIcon;
    bool IsBkColorEnabled;
    QColor Bkclor;

private slots:
    void smSLOT();

};

#endif
