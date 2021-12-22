#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include "globals.h"
#include "mkn.h"

QT_BEGIN_NAMESPACE
//class QDragEnterEvent;
//class QDropEvent;
//class DragWidget;
class IEcard;
//QT_END_NAMESPACE

//! [0]
class DragWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);


    static int count;
    static int col;
    static int row;
  //  hC_IEDET* isEmriDetay;
  //  hC_IE* isEmri;
    hC_MKN* mkn;



signals:
    void sgnDragger();
private:

//    void isEmriYeni(QSqlRecord record);
  //  void isEmriListele();


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;


};
//! [0]
//!
//!



class IEcard : public QWidget//DragWidget
{
    Q_OBJECT

public:
    IEcard(int ieno, QWidget *parent = nullptr) ;
    ~IEcard() ;//override;


    QLabel* resim;

    int getObjNo() const;
    void setObjNo(int value=0);

    QSqlRecord getRecord() const;
    void setRecord(QSqlRecord value);

    int getIeno() const;
    void setIeno(int value = 0 );

    QString getKurumno() const;
    void setKurumno(QString value=nullptr);

    QPixmap getPixmapie() const;
    void setPixmapie(QPixmap value);

    QPixmap getPixmapmkn() const;
    void setPixmapmkn(const QPixmap value);

    QString getPaintObjNo() const;
    void setPaintObjNo(const QString value);

protected:
    void paintEvent(QPaintEvent *) ;//override;
    void mousePressEvent(QMouseEvent *event);// override;
  //  void mouseDoubleClickEvent( QMouseEvent * e ) override;
private:
    //int objNo;

    QPixmap SimileIcon;


    int objNo;
    QString paintObjNo;
    int ieno;
    QString kurumno;
    QPixmap pixmapie;
    QPixmap pixmapmkn;



private slots:
    void smSLOT();


};

#endif
