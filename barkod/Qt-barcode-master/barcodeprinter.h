#ifndef BARCODEPRINTER_H
#define BARCODEPRINTER_H

#include <QObject>
#include <QtPrintSupport>

#define CODE128_B_START 104
#define CODE128_STOP 106

class BarcodePrinter : public QWidget
{
    Q_OBJECT
public:
    explicit BarcodePrinter(QString barcodeText, QWidget *parent = nullptr);
    ~BarcodePrinter() ;
    /** Lists all available printers */
    QStringList getAvailablePrinters();
    /** Configures the printer, if none selected defaults to pdf printer */
    bool configurePrinter(QString printerName = QString());
    QString *barcodeText;
    /** Prints the text as a barcode */
public slots:

    void printBarcode(QString barcodeText);



private:
    /** Configures the page */
    void configurePage();

    /** Adds start/check/stop characters to the code */
    QString encodeBarcode(QString code);

    /** Calculates the checksum character from the code */
    int calculateCheckCharacter(QString code);

    int codeToChar(int code);
    int charToCode(int ch);

    bool printerConfigured;
    QPrinter *mPrinter;

};

#endif // BARCODEPRINTER_H


