#include <QPainter>
#include <QDebug>

#include "ean13.h"

/************************************************
********************************/
EAN13::EAN13(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint
              | Qt::WindowSystemMenuHint)
{
    // Set up constant data

    LCode << "0001101" << "0011001" << "0010011" <<"0111101" << "0100011"
          << "0110001" << "0101111" << "0111011" << "0110111" << "0001011";

    GCode << "0100111" << "0110011" << "0011011" << "0100001" << "0011101"
          << "0111001" << "0000101" << "0010001" << "0001001" << "0010111";

    RCode << "1110010" << "1100110" << "1101100" << "1000010" << "1011100"
          << "1001110" << "1010000" << "1000100" << "1001000" << "1110100";

    Parity << "000000" << "001011" << "001101" << "001110" << "010011"
           << "011001" << "011100" << "010101" << "010110" << "011010";

    quietZone = "000000000";
    leadTail = "101";
    separator = "01010";

    nominalWidth = 37.29;
    nominalHeight = 25.93;
    nominalFontSize = 8.0;
}

/************************************************
********************************/
void EAN13::makePattern(const QString &code)
{
    int i, sum, digit ;

    // limit to 13 characters
    barcode = code.left(13) ;

    sum = digit = 0 ;
    // calculate checksum digit
    for(i = 0 ; i < barcode.length() ; i++)
    {
        digit = barcode.mid(i, 1).toInt() ;
        if(i % 2 == 0)
            sum += digit ;	    // odd
        else
            sum += digit * 3 ;  // even
    }
    checksum = (10 -(sum % 10)) % 10 ;
    barcode += QString::number(checksum) ;

    // build the EAN code pattern
    pattern = quietZone + leadTail ;

    parity = Parity[barcode.left(1).toInt()] ;
    // convert left hand numbers
    for(int i = 1; i <= 6; i++) {
        if(parity.mid(i - 1, 1).toInt())
            pattern.append(convertToDigitPattern(barcode.mid(i, 1), GCode));
        else
            pattern.append(convertToDigitPattern(barcode.mid(i, 1), LCode));
    }

    pattern += separator +
            convertToDigitPattern(barcode.mid(7,6), RCode) +
            leadTail +
            quietZone ;

    countryCode = barcode.mid(0, 1) ;
    leftCode = barcode.mid(1, 6) ;
    rightCode = barcode.mid(7, 6) ;
}

/************************************************
********************************/
void EAN13::draw(const QRectF &rect, QPainter &painter, const QString &code)
{
    makePattern(code) ;
    draw(rect, painter) ;
}

/************************************************
********************************/
void EAN13::draw(const QRectF &rect, QPainter &painter)
{
    int i ;

    painter.save();
    painter.setViewport(int(rect.x()), int(rect.y()), int(rect.width()), int(rect.height()));
    painter.setWindow(0, 0, int(rect.width()), int(rect.height()));
    painter.fillRect(painter.window(), Qt::white);	        // set background

    qreal width = rect.width();
    qreal height = rect.height();
    qreal barWidth = width / 113;

    qreal nominalWidthInPixels = nominalWidth * painter.device()->logicalDpiX() / 25.4;
    qreal fontScale = width / nominalWidthInPixels;

    painter.setRenderHint(QPainter::Antialiasing, true);
    QFont font("arial");
    font.setPointSizeF(nominalFontSize * fontScale);
    painter.setFont(font);
    painter.setPen(Qt::SolidLine);
    painter.setPen(Qt::black);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);

    qreal textHeight = painter.boundingRect(0, 0, 0, 0, 0, pattern.mid(0,1)).height();

    painter.save();
    painter.setPen(Qt::NoPen);

    for(i = 0; i < pattern.length(); i++) {                               // draw the barcode lines
        if(pattern.mid(i, 1) == "1") {
            if((i > 12 && i < 55) || (i > 57 && i < 101))
                painter.drawRect(QRectF(0, 0, barWidth, height - textHeight));     // draw with space for the number
            else
                painter.drawRect(QRectF(0, 0, barWidth, height));                  // draw a full line
        }
        painter.translate(barWidth, 0);
    }
    painter.restore();

    // draw the numbers below the line
    QRectF countryCodeRect(painter.boundingRect(QRectF(0, 0, 0, 0), Qt::AlignRight,	countryCode));
    QRectF leftCodeRect(painter.boundingRect(QRectF(0, 0, 0, 0), Qt::AlignHCenter, leftCode));
    QRectF rightCodeRect(painter.boundingRect(QRectF(0, 0, 0, 0), Qt::AlignHCenter, rightCode));
    QRectF checksumRect(painter.boundingRect(QRectF(0, 0, 0, 0), Qt::AlignLeft, checksumDigit));

    painter.translate(8 * barWidth, height - countryCodeRect.height());
    painter.drawText(countryCodeRect, Qt::AlignRight, countryCode);          // draw 1st digit of country code

    painter.translate((25 * barWidth), 0);
    painter.drawText(leftCodeRect, Qt::AlignHCenter, leftCode);              // draw manufacturer number

    painter.translate((47 * barWidth), 0);
    painter.drawText(rightCodeRect, Qt::AlignHCenter, rightCode);            // draw product id

    painter.translate((26 * barWidth), 0);
    painter.drawText(checksumRect, Qt::AlignLeft, checksumDigit);            // draw checksum digit

    painter.restore();
}

/************************************************
********************************/
QString EAN13::convertToDigitPattern(QString number, QStringList &pattern)
{
    QString digitPattern = "" ;

    for(int i = 0; i < number.length(); i++) {
        int index = number.mid(i, 1).toInt();
        digitPattern.append(pattern[index]);
    }

    return(digitPattern) ;
}

/************************************************
********************************/
