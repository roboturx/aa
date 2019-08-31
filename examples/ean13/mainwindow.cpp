#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtPrintSupport/QPrinter>

/************************************************
********************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(100,100, 700, 500) ;

    barcode = new EAN13(this);
    barcodeStr = "0048572020000" ;

    connect(ui->CodeEdit , SIGNAL(textChanged() ), this,
            SLOT(updateSwtClicked())) ;
    connect(ui->UpdateSwt, SIGNAL(clicked()), this,
            SLOT(updateSwtClicked())) ;
    connect(ui->PrintSwt, SIGNAL(clicked()), this,
            SLOT(printSwtClicked())) ;

}

/************************************************
********************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/************************************************
********************************/
void MainWindow::resizeEvent(QResizeEvent * /* event */)
{
}

/************************************************
********************************/
void MainWindow::paintEvent(QPaintEvent *event)
{
    // evade compiler warning
    event = event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    draw(&painter);
}

/************************************************
********************************/
void MainWindow::draw(QPainter *painter)
{
    barcode->makePattern(barcodeStr);

    painter->drawText(50,70,"Arbitrary size");
    barcode->draw(QRectF(50, 80, width() - 100, height() - 300), *painter) ;

    painter->drawText(50, height() - 160,"Nominal size (37.29mm x 25.93mm)");
    qreal scale = painter->device()->physicalDpiX() / 25.4;	// dots per mm
    barcode->draw(QRectF(50, height() - 150, 37.29 * scale, 25.93 * scale), *painter);
}

/******************************************************
**************************/
void MainWindow::updateSwtClicked()
{
    barcodeStr = ui->CodeEdit->text() ;
    update() ;
}

/*******************************************************
*************************/
void MainWindow::printSwtClicked()
{

    QPrinter printer ;
    int Wd, Ht ;

    if(width() > height())
        printer.setOrientation(QPrinter::Landscape) ;
    else
        printer.setOrientation(QPrinter::Portrait) ;

    Wd = printer.width() ;
    Ht = printer.height() ;

    QPainter painter ;
    painter.begin(&printer);

    barcode->makePattern(barcodeStr);

    painter.drawText(50,30,"EAN13 Barcode test generator");

    painter.drawText(50,70,"Arbitrary size");
    barcode->draw(QRectF(50, 80, Wd - 100, Ht - 300), painter) ;

    painter.drawText(50, Ht - 160,"Nominal size (37.29mm x 25.93mm)");
    qreal scale = painter.device()->logicalDpiX() / 25.4;	// dots per mm
    barcode->draw(QRectF(50,
                         Ht - 150,
                         37.29 * scale,
                         25.93 * scale ), painter);

    painter.end();
}

/************************************************
********************************/

