#ifndef EAN13_H
#define EAN13_H

#include <QWidget>
#include <QStringList>
#include <QImage>

/********************************************************************************/
class EAN13 : public QWidget
{
public:
        EAN13(QWidget *parent = 0);
        void makePattern(const QString &code) ;
        void draw(const QRectF &rect, QPainter &painter, const QString &code);
        void draw(const QRectF &rect, QPainter &painter);

private:
        QRectF      *codeRect;				// bounds of this device

        QStringList LCode;
        QStringList GCode;
        QStringList RCode;
        QStringList Parity;
        QString     quietZone;
        QString     leadTail;
        QString     separator;
        QString     checksumDigit;
        qreal       nominalWidth;
        qreal       nominalHeight;
        qreal       nominalFontSize;
        int         checksum ;

        QString     barcode;
        QString     parity ;
        QString     pattern ;
        QString     countryCode, leftCode, rightCode ;

        QString     convertToDigitPattern(QString number, QStringList &pattern);
};

/********************************************************************************/

#endif // EAN13_H
