#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QtPrintSupport/QPrinter>

#include "ean13.h"

namespace Ui {
    class MainWindow;
}

/********************************************************************************/
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event) ;

private:
    Ui::MainWindow *ui;
    EAN13   *barcode ;
    QString barcodeStr ;

    void  draw(QPainter *painter) ;

public slots:
    void  updateSwtClicked() ;
    void  printSwtClicked() ;

};

/********************************************************************************/

#endif // MAINWINDOW_H
