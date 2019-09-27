#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "code128item.h"
#include "QPrintDialog"
#include "QPrinter"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPrinter *mPrinter;

    QGraphicsScene *m_Scene;
    Code128Item * m_Barcode;



private slots:
    void on_pushButton_clicked();
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_lineEdit_4_textChanged(const QString &arg1);
    void on_lineEdit_5_textChanged(const QString &arg1);

public slots:
    void filePrintPreview();            // display print preview dialog
    void filePrint();                   // display print dialog
    void print( QPrinter* );            // draw print page


private:
    Ui::MainWindow *ui;
    void tazele();
};

#endif // MAINWINDOW_H
