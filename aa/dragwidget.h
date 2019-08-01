#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include "globals.h"
//#include "iedet.h"
//#include "iedet.h"
#include "mkn.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class DragWidget;
class IEcard;
QT_END_NAMESPACE

//! [0]
class DragWidget : public QWidget
{
public:
    explicit DragWidget(QWidget *parent = nullptr);


    static int count;
    static int col;
    static int row;
  //  hC_IEDET* isEmriDetay;
  //  hC_IE* isEmri;
    hC_MKN* mkn;


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



class IEcard : public DragWidget
{
    Q_OBJECT

public:
    IEcard(QWidget *parent = nullptr) ;
    ~IEcard() override;

    int objNo;
    QString paintObjNo;
    QString ieno;
    QString kurumno;
    QPixmap pixmapie;
    QPixmap pixmapmkn;
    QSqlRecord record;

    void setDefaults(QDataStream *dataStream);
    QLabel* resim;

    int getObjNo() const;
    void setObjNo(int value=0);

    QSqlRecord getRecord() const;
    void setRecord(QSqlRecord value);

    QString getIeno() const;
    void setIeno(QString value=nullptr );

    QString getKurumno() const;
    void setKurumno(QString value=nullptr);

    QPixmap usedPixmapie();
    QPixmap getPixmapie() const;
    void setPixmapie(QPixmap value);

    void usedPixmapmkn( QByteArray mkn_pX) ;
    QPixmap getPixmapmkn() const;
    void setPixmapmkn(const QPixmap &value);

    QString getPaintObjNo() const;
    void setPaintObjNo(const QString &value);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
  //  void mouseDoubleClickEvent( QMouseEvent * e ) override;
private:
    //int objNo;

    QImage SimileIcon;
    bool IsBkColorEnabled;
    QColor Bkclor;

private slots:
    void smSLOT();

};

#endif
