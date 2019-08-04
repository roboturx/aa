#ifndef hC_IE_H
#define hC_IE_H

#include <globals.h>
//#include "dragwidget.h"
#include "mkn.h"

namespace nSIe {
class hC_IE;
}

class hC_IE : public hC_tBcreator
{
    Q_OBJECT

public:
    explicit hC_IE(QWidget *parent=nullptr);
    ~hC_IE() override;

    hC_ArrD                  * tb_flds   {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QByteArray * mknrsm_bA;
    QByteArray * son_bA;
    QPixmap * qpm ;

    hC_MKN *mkn;

    hC_Le* hClE_mkn;

    QLineEdit* lE_ieno;
    QDateTimeEdit* dE_geltar;
    QComboBox* cbX_durum;
    QDateTimeEdit* dE_girtar;
    QDateTimeEdit* dE_ciktar;
    hC_Le* hClE_yetkili1;
    hC_Le* hClE_yetkili2;

    void tbsetup () ;

    static int x;
    static int y;



private:
    void tbwdgt  () ;
    void tbui    () ;
    void tbkntrl () ;


    void isEmriListele();
    void isEmriYeni(int ieno_nT,
                    QString kurumno_sT,
                    QDateTime tarih_dT,
                    QString durum_sT,
                    QDateTime girtar_dT,
                    QDateTime ciktar_dT,
                    QString y1_sT,
                    QString y2_sT,
                    QByteArray iersmmkn_bA,
                    QByteArray iersmie_bA,
                    QPoint iepos );
public: signals:
    void sgnIsEmri (int);


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;


};



class IEcard : public QWidget//DragWidget
{
    Q_OBJECT

public:
    IEcard(int ieno, QWidget *parent = nullptr) ;
    ~IEcard() ;//override;

    QString ietooltip();

    int getIeno_nT() const;
    void setIeno_nT(int value = 0 );

    QString getKurumno_sT() const;
    void setKurumno_sT(const QString value);

    QDateTime getTarih_dT() const;
    void setTarih_dT(const QDateTime value);

    QString getDurum_sT() const;
    void setDurum_sT(const QString value);

    QDateTime getGirtar_dT() const;
    void setGirtar_dT(const QDateTime value);

    QDateTime getCiktar_dT() const;
    void setCiktar_dT(const QDateTime value);

    QString getY1_sT() const;
    void setY1_sT(const QString value);

    QString getY2_sT() const;
    void setY2_sT(const QString value);

    QPixmap getIemkn_pX() const;
    void setIemkn_pX(const QPixmap value);

    QPixmap getIe_pX() const;
    void setIe_pX(const QPixmap value);

    QPoint getIepos_pT() const;
    void setIepos_pT(const QPoint value);

protected:
    void paintEvent(QPaintEvent *) ;//override;
    void mousePressEvent(QMouseEvent *event);// override;
    //  void mouseDoubleClickEvent( QMouseEvent * e ) override;
private:

    //    QPixmap SimileIcon;





    int ieno_nT;
    QString kurumno_sT ;
    QDateTime tarih_dT ;
    QString durum_sT ;
    QDateTime girtar_dT ;
    QDateTime ciktar_dT ;
    QString y1_sT ;
    QString y2_sT ;
    QPixmap iemkn_pX;
    QPixmap ie_pX;
    QPoint iepos_pT;

private slots:
    void smSLOT();


};

QDataStream &operator <<
(QDataStream &streamGotFromObject,
 const IEcard &IEcard);




QDataStream &operator >>(QDataStream &streamSentToObject,
                                 IEcard &IEcard);

#endif // hC_IE_H
