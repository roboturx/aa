#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi (this);
    qDebug()<<"1";

    m_Scene = new QGraphicsScene(this) ;
    ui->graphicsView->setScene (m_Scene);
    m_Barcode = new Code128Item();
    m_Barcode->setWidth( 100 );   // barkod kendi
    m_Barcode->setHeight( 80 );
    m_Barcode->setPos(0,0);
    m_Barcode->setText("Murat Balcı");
    m_Barcode->setHighDPI (true);
    m_Scene->addItem( m_Barcode );

    mPrinter = new QPrinter( QPrinter::HighResolution );
    ui->lineEdit->setText("Murat-123456");
    ui->lineEdit_2->setText("0");
    ui->lineEdit_3->setText ("0");
    ui->lineEdit_4->setText ("100");
    ui->lineEdit_5->setText ("200");



}
/********************************* filePrintPreview **********************************/

void  MainWindow::filePrintPreview()
{
    // display print preview dialog

    QPrintPreviewDialog  preview( mPrinter, this );
    connect( &preview, SIGNAL(paintRequested(QPrinter*)),
             SLOT(print(QPrinter*)) );
    preview.setGeometry (100,400,800,400);
    preview.setWindowTitle ("Barkod Yazıcı");
    preview.exec();

}



void  MainWindow::filePrint()
{
    // display print dialog and if accepted print
    //  QPrinter       mPrinter( QPrinter::HighResolution );
    QPrintDialog   dialog( mPrinter, this );
    if ( dialog.exec() == QDialog::Accepted )
    {



    }

}

void  MainWindow::print( QPrinter* mPrinter )
{
    mPrinter->setOrientation(QPrinter::Landscape);
    QPainter painter( mPrinter);
    QRectF target(mPrinter->pageRect ());
    QRectF source(ui->lineEdit_2->text ().toFloat (),
                  ui->lineEdit_3->text ().toFloat (),
                  ui->lineEdit_4->text ().toFloat (),
                  ui->lineEdit_5->text ().toFloat ());
    m_Scene->render(&painter,target,source);
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->filePrintPreview ();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    m_Barcode->setText(arg1);
    m_Barcode->update();
    m_Scene->update();

}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    tazele();
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    tazele();
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    tazele();
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    tazele();
}
void MainWindow::tazele()
{
    m_Scene->setSceneRect (ui->lineEdit_2->text ().toInt (),
                           ui->lineEdit_3->text ().toInt (),
                           ui->lineEdit_4->text ().toInt (),
                           ui->lineEdit_5->text ().toInt () );

    m_Scene->update();

}
