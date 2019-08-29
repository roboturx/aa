#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QDebug>
#include "barcodeprinter.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  /*  ui->setupUi (this);
    qDebug()<<"1";

    m_Scene = new QGraphicsScene(this) ;
    m_Scene->setSceneRect(0, 0, 100, 80);
    ui->graphicsView->setScene (m_Scene);
    m_Barcode = new Code128Item();
    m_Barcode->setWidth( 100 );   // barkod kendi
    m_Barcode->setHeight( 80 );
    m_Barcode->setPos(50,40);
    m_Barcode->setText("Murat Balcı");
    m_Barcode->setHighDPI (true);
    m_Scene->addItem( m_Barcode );
*/
    BarcodePrinter bp ("m_Barcode",this);
return;


    mPrinter = new QPrinter( QPrinter::HighResolution );
    mPrinter->setFullPage(false);
    // this results in empty page (or is ignored if my rect is 8 in)
    //printer.setPaperSize(canvasRect, QPrinter::Point);
    mPrinter->setOrientation(QPrinter::Landscape);
    mPrinter->setPageMargins(0, 0, 0, 0, QPrinter::Point);


    ui->lineEdit->setText("Murat-123456");
    ui->lineEdit_2->setText("0");
    ui->lineEdit_3->setText ("0");
    ui->lineEdit_4->setText ("100");
    ui->lineEdit_5->setText ("80");



}
/********************************* filePrintPreview **********************************/

void  MainWindow::filePrintPreview()
{
    // display print preview dialog

  /*  QPrintPreviewDialog  preview( mPrinter, this );
    connect( &preview, SIGNAL(paintRequested(QPrinter*)),
             SLOT(print(QPrinter*)) );
    preview.setGeometry (0,0,800,400);
    preview.setWindowTitle ("Barkod Yazıcı");
    preview.exec();
    */

    //QPrinter printer;
        // QPrinter printer(QPrinter::HighResolution);  // this makes no difference except it rotates the output, strange

        // without this just to use default printer, if you like
        QPrintPreviewDialog preview( mPrinter,this );

        connect( &preview , SIGNAL(paintRequested(QPrinter*)),
                 SLOT(print(QPrinter*)) );
//        preview.setGeometry (0,0,800,400);
        preview.setWindowTitle ("Barkod Yazıcı");

        if (preview.exec() != QDialog::Accepted)
        {
          qDebug() <<"return 1" ;
        }






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
  /*  mPrinter->setOrientation(QPrinter::Landscape);
    QPainter painter( mPrinter);
    QRect target(500,500,1000,800   );//mPrinter->pageRect ());
    QRect source(ui->lineEdit_2->text ().toInt (),
                  ui->lineEdit_3->text ().toInt (),
                  ui->lineEdit_4->text ().toInt (),
                  ui->lineEdit_5->text ().toInt ());
    //m_Scene->render(&painter,target,source,Qt::KeepAspectRatio);
    ui->graphicsView->render(&painter,target,source,Qt::KeepAspectRatio);
*/
/////////////////////////////////////////////////////////////////////////
    int canvasSize = 288;    // 4 in
    QRectF canvasRect(0, 0, canvasSize, canvasSize);

    QPainter painter(mPrinter);

 //   if (painter.begin(mPrinter))
  //  {
//        painter.setClipRect(canvasRect);  // this creates a small clipping, only a tiny corner
        m_Scene->render(&painter, QRectF(), canvasRect, Qt::KeepAspectRatio);
        // doing this instead clips to a tiny rectangle also
//        s->render(&painter, canvasRect, canvasRect, Qt::KeepAspectRatio);
    //    painter.end();
   // }
   // else {
     //   qDebug ()<<" painter başlamadı";
   // }



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
   // this->filePrintPreview ();

}
