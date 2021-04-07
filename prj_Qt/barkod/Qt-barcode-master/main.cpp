#include <QApplication>
#include "barcodeprinter.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    BarcodePrinter *printer = new BarcodePrinter();

    w.show ();
    a.exec ();
    return 0;
}




