#include "barcodeprinter.h"
#include <QPrinter>
#include <QFont>
#include <QPrintDialog>


BarcodePrinter::BarcodePrinter(QString barcodeText ,
                   QWidget *parent) : QWidget(parent)
{

    //BarcodePrinter *printer = new BarcodePrinter();

    mPrinter = new QPrinter;

    QPrintDialog printDialog(mPrinter, this);
    if (printDialog.exec() == QDialog::Rejected )
    {
        return;
    }

        qDebug()<<"Yazılıyor :";
 //       configurePage ();
        printBarcode (barcodeText);



    //getAvailablePrinters();

    //Configure printer (no argument means it prints pdf)
    //configurePrinter( );

    //Print barcode
}

BarcodePrinter::~BarcodePrinter()
{

}

void BarcodePrinter::printBarcode(QString barcodeText)
{
  //  if(!printerConfigured)
   // {
    //    qDebug() << "Printer not configured, abort.";
    //    return;
   // }

    qDebug() << "Printing : \"" + barcodeText + "\" ...";

    double MmToDot = 8; //Printer DPI = 203 => 8 dots per mm
    QPainter painter(mPrinter);

    QRect barcodeRect = QRect(5*MmToDot,10*MmToDot,67.5*MmToDot,10*MmToDot);
    QRect barcodeTextRect = QRect(5*MmToDot,20.5*MmToDot,67.5*MmToDot,5*MmToDot);

    //QFont barcodefont = QFont("Code 128", 46, QFont::Normal);
    QFont barcodefont = QFont("Code 128", 22, QFont::Normal);
    barcodefont.setLetterSpacing(QFont::AbsoluteSpacing,0.0);
    painter.setFont(barcodefont);

    QString arr = encodeBarcode(barcodeText);
    painter.drawText(barcodeRect, Qt::AlignCenter, arr);

    painter.setFont(QFont("PT Sans", 10));
    painter.drawText(barcodeTextRect, Qt::AlignCenter, barcodeText);

    painter.end();

    qDebug() << "Printing finished-----------------------------";
}

void BarcodePrinter::configurePage()
{
    //
    mPrinter->setColorMode(QPrinter::GrayScale);
    mPrinter->setPageSizeMM(QSizeF(80,40));
    mPrinter->setPaperSize(QSizeF(80,40), QPrinter::Millimeter);
    mPrinter->setResolution(203);
    mPrinter->setPageMargins(0,0,0,0, QPrinter::Millimeter);
    mPrinter->setOrientation(QPrinter::Portrait);
    qDebug() << "Page Configured";
}

QString BarcodePrinter::encodeBarcode(QString code)
{
    QString encoded;

    //Start set with B Code 104
    ///encoded.prepend(QChar(codeToChar(CODE128_B_START)));

    //encoded.append();
    encoded.append(code);
    encoded.append(QChar(calculateCheckCharacter(code)));
    //End set with Stop Code 106
    encoded.append(QChar(codeToChar(CODE128_STOP)));

    return encoded;
}

int BarcodePrinter::calculateCheckCharacter(QString code)
{
    QByteArray encapBarcode(code.toUtf8()); //Convert code to utf8

    //Calculate check character
    //The sum starts with the B Code start character value
    long long sum = CODE128_B_START;
    //Initial weight is 1
    int weight = 1;

    foreach(char ch, encapBarcode)
    {
        //Calculate character code
        int code_char = charToCode((int)ch);
        //add weighted code to sum
        sum += code_char*weight;
        //increment weight
        weight++;
    }

    int remain = sum%103; //The check character is the modulo 103 of the sum

    //Calculate the font integer from the code integer
    if(remain >= 95)
        remain += 105;
    else
        remain += 32;

    return remain;
}

int BarcodePrinter::codeToChar(int code)
{
    return code + 105;
}

int BarcodePrinter::charToCode(int ch)
{
    return ch - 32;
}







QStringList BarcodePrinter::getAvailablePrinters()
{
    QStringList availablePrinters;

    qDebug()<<"Yazıcılar :";
    QPrinterInfo pInfo;
    foreach (QPrinterInfo info, pInfo.availablePrinters())
    {
        availablePrinters << info.printerName();
        qDebug()<<"Yazıcı :"<<info.printerName();
    }

    return availablePrinters;
}



bool BarcodePrinter::configurePrinter(QString printerName)
{
    bool printerAvailable = getAvailablePrinters().
                              contains(printerName);
    if(printerAvailable)
    {
        mPrinter->setPrinterName(printerName);
        configurePage();
qDebug() << printerName << " yazıcı hazır" ;
        qDebug() << &"Printer initialized. State: " [ mPrinter->printerState()] ;
    }
    else //If the printer is unavailable, generate pdf instead
    {
        mPrinter->setOutputFileName("barcode.pdf");
        mPrinter->setOutputFormat(QPrinter::PdfFormat);
        configurePage();

        qDebug() << "Printer initialized to generate pdf";
    }

    printerConfigured = true;

    return printerAvailable;

}
