

#include "frmAna.h"
#include "ui_frmAna.h"
#include "QSqlQueryModel"
#include "frmUrun.h"
#include "frmHkk.h"
#include "frmGrs.h"
#include <QTextStream>
#include "VTKontrol.h"
#include <QStyle>
#include <QApplication>
//#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QAction>
#include <QString>
#include <QSqlError>
#include <QCloseEvent>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QScreen>

frmAna::frmAna(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::frmAna){
    this->setVisible(false);
    this->hide();
// ana ekran gizlendi
    ui->setupUi(this);
   // window()->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window()->size(), qApp->desktop()->availableGeometry()));
    this->statusBar()->setSizeGripEnabled(false);
  //  this->setFixedSize(this->maximumSize());


    QSize size = qApp->screens()[0]->size();
    this->resize(size*.9);


    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->dteSearchByDateAddMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateAddMax->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateUpdateMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateUpdateMax->setDateTime(QDateTime::currentDateTime());

    ui->tblProducts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblProducts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblProducts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblProducts->resizeColumnsToContents();
    ui->tblProducts->resizeRowsToContents();
    ui->tblProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tblProducts->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Stretch);


    ui->txtSearchByBarkod->setEnabled(false);
    //ui->cbSearchByBarkod->setEnabled(false);
    ui->txtSearchByName->setEnabled(false);
    ui->cbSearchByNamePattern->setEnabled(false);
    ui->cbSearchByDateAdd->setEnabled(false);
    ui->cbSearchByDateUpdate->setEnabled(false);
    ui->dteSearchByDateAddMin->setEnabled(false);
    ui->dteSearchByDateAddMax->setEnabled(false);
    ui->dteSearchByDateUpdateMin->setEnabled(false);
    ui->dteSearchByDateUpdateMax->setEnabled(false);
    ui->sbSearchByQuantity->setEnabled(false);
    ui->cbSearchByQuantityPattern->setEnabled(false);
    ui->cbSearchByPricePurchase->setEnabled(false);
    ui->cbSearchByPriceSale->setEnabled(false);
    ui->dsbSearchByPricePurchase->setEnabled(false);
    ui->cbSearchByPricePurchasePattern->setEnabled(false);
    ui->dsbSearchByPriceSale->setEnabled(false);
    ui->cbSearchByPriceSalePattern->setEnabled(false);

// veritabnını setup ve connect

    VTKontrolEt::instance()->SetupDB();

    if(VTKontrolEt::instance()->Connect()){
        QTextStream(stdout) << "İlk Bağlantı Açıldı ...";
    } else {
        QTextStream(stdout) << "İlk Bağlantı Açılamadı !!!";
    }


    m_frmUrun = new frmUrun(this);
    m_frmGrs = new frmGrs(this);

    bool signalAbout =
            connect(ui->actAbout, SIGNAL(triggered()),
                            this, SLOT(showMenuAbout()));
    Q_ASSERT(signalAbout);

    bool signalQuit =
            connect(ui->actQuit, SIGNAL(triggered()),
                    this, SLOT(quitApp()));
    Q_ASSERT(signalAbout);

    bool signalOK =
            connect(m_frmUrun, SIGNAL(Refresh()),
                    this, SLOT(on_btnRefresh_clicked()));
    Q_ASSERT(signalOK);

    bool signalAccount =
            connect(m_frmGrs, SIGNAL(LoginOK(QString)),
                    this, SLOT(loginOKWith(QString)));
    Q_ASSERT(signalAccount);

    m_frmGrs->show();
}

frmAna::~frmAna()
{
    delete ui;
}

void frmAna::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton mboxSelect = QMessageBox::question( this, "Okul Takip Yazılımı", "Çıkmak istediğinizden emin misiniz?", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (mboxSelect != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        quitApp();
    }
}

void frmAna::quitApp(){
    try {
        QMessageBox::StandardButton mboxSelect =
                QMessageBox::question( this,
               "Tıp Puanlama 2014-2017 Yazılımı",
               "Çıkmak istediğinizden emin misiniz?",
               QMessageBox::Cancel | QMessageBox::No |
                  QMessageBox::Yes, QMessageBox::Yes);

        if (mboxSelect != QMessageBox::Yes) {
            return;
        } else {
            if(VTKontrolEt::instance()->IsOpen())
            {
                VTKontrolEt::instance()->Disconnect();
                ui->statusbar->showMessage("Veritabanı bağlantısı KAPATILDI ...", 1000);
                QTextStream(stdout) << "Bağlantı KAPATILDI ...";
            }
            QApplication::quit();
        }
    } catch (...) {
        qDebug() << "Hata";
        QApplication::exit(1);
    }
}

void frmAna::showMenuAbout()
{
    frmHkk * frm = new frmHkk();
    frm->setModal(true);
    frm->show();
    qDebug() << "Hakkında ....";
}

void frmAna::loginOKWith(QString name){
    m_frmGrs->hide();
    this->show();
    this->setVisible(true);
    this->setWindowOpacity(1);
// veritabnı açık mı
    if(VTKontrolEt::instance()->IsOpen()){
        ui->statusbar->showMessage("Veritabanı bağlantısı Açık ...", 1000);
        QTextStream(stdout) << "Bağlantı Açık ...";

        LoadProducts();
    } else{
        QMessageBox::critical(this, "HATA VAR Bağlantı KAPALI", VTKontrolEt::instance()->GetError());
        QTextStream(stdout) << "Bağlantı KAPALI !!!";
    }

    ui->lblAccountInfo->setText(name);
}

void frmAna::LoadProducts(){
    qDebug() << "listele ";

    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare( "SELECT * FROM product" );

    if (query.exec()){
        if(query.isActive()){
            qDebug() << "Okul listelemele tamam...";
            queryModel->setQuery(query);

            queryModel->setHeaderData(0, Qt::Horizontal, "ID");
            queryModel->setHeaderData(1, Qt::Horizontal, "Okul");
            queryModel->setHeaderData(2, Qt::Horizontal, "Açıklama");
            queryModel->setHeaderData(3, Qt::Horizontal, "Yıl");
            queryModel->setHeaderData(4, Qt::Horizontal, "Kontenjan");
            queryModel->setHeaderData(5, Qt::Horizontal, "Yerleşen");
            queryModel->setHeaderData(6, Qt::Horizontal, "Sıralama");
            queryModel->setHeaderData(7, Qt::Horizontal, "Puan");
            queryModel->setHeaderData(8, Qt::Horizontal, "Fiyat");
            queryModel->setHeaderData(9, Qt::Horizontal, "İndirim");
            queryModel->setHeaderData(10, Qt::Horizontal, "Ödenecek");
            ui->tblProducts->setModel(queryModel);
            ui->statusbar->showMessage("Okul Listeleme tamam ... " + queryModel->rowCount());
        } else {
            QMessageBox::critical(this, "HATA VAR", "Sorgu hatası");
            qDebug() << query.lastError();
            return;
        }
    } else {
        QMessageBox::warning(this, "Okul", "Okul listelemede hata !!!");
        qDebug() << query.lastError();
        return;
    }



}

void frmAna::on_btnRefresh_clicked()
{
    this->LoadProducts();
}

void frmAna::on_btnProductOperations_clicked()
{    
    m_frmUrun->setModal(true);
    m_frmUrun->show();
    m_frmUrun->Clear();
}

void frmAna::on_tblProducts_activated(const QModelIndex &index)
{
    m_frmUrun->setModal(true);
    m_frmUrun->show();
    m_frmUrun->LoadProduct(index.row());
}

void frmAna::on_tblProducts_pressed(const QModelIndex &index)
{
    LoadProductInfoToLabel(index);
}

void frmAna::LoadProductInfoToLabel(const QModelIndex &index){
  //  QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare(
       "SELECT * FROM product "
       "WHERE id = :id AND barcode = :name"  );

    query.bindValue(":id", index.sibling(index.row(), 0).data().toInt());
    query.bindValue(":name", index.sibling(index.row(), 1).data().toString());

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){

                ui->lblProductInfo->setText("Okul: " +
                    query.value(1).toString() + " - " +
                    index.model()->headerData(index.column(),
                    Qt::Horizontal).toString() + ": " +
                    index.sibling(index.row(),
                    index.column()).data().toString());

                qDebug() << "Okul bilgisi...: " << query.executedQuery();
            }
        }
    } else {
        QMessageBox::warning(this, "Okul", "Sorguda Hata...");
        qDebug() << query.lastError();
        return;
    }
}


void frmAna::on_btnSearch_clicked()
{
    QString queryString = "SELECT * FROM product ";
    QString queryStringWhereConcatenator = "WHERE ";

    if(ui->cbSearchByName->checkState()){
        QString productName = ui->txtSearchByName->text().trimmed();
        if(!productName.isEmpty() && productName.length() > 0){
            queryString += queryStringWhereConcatenator;
            if(ui->cbSearchByNamePattern->currentIndex() == 0){ //Exactly
                queryString += "name = '" + productName + "' ";
            } else if (ui->cbSearchByNamePattern->currentIndex() == 1){ //Stars With
                queryString += "name like '" + productName + "%' ";
            } else if (ui->cbSearchByNamePattern->currentIndex() == 2){ //Ends With
                queryString += "name like '%" + productName + "' ";
            }
            queryStringWhereConcatenator = "AND ";
        } else {
            QMessageBox::warning(this, "Arama", "Okul adı ile aramak için okul adı giriniz ...");
            return;
        }
    }




    qDebug() << "Arama ... " << queryString;

    QSqlQuery query;
    query.prepare(queryString);

     QSqlQueryModel * queryModel = new QSqlQueryModel();

     if (query.exec()){
         if(query.isActive()){
             qDebug() << "Arama Tamam";
             queryModel->setQuery(query);

             queryModel->setHeaderData(0, Qt::Horizontal, "ID");
             queryModel->setHeaderData(1, Qt::Horizontal, "Okul");
             queryModel->setHeaderData(2, Qt::Horizontal, "Açıklama");
             queryModel->setHeaderData(3, Qt::Horizontal, "Yıl");
             queryModel->setHeaderData(4, Qt::Horizontal, "Kontenjan");
             queryModel->setHeaderData(5, Qt::Horizontal, "Yerleşen");
             queryModel->setHeaderData(6, Qt::Horizontal, "Sıralama");
             queryModel->setHeaderData(7, Qt::Horizontal, "Puan");
             queryModel->setHeaderData(8, Qt::Horizontal, "Fiyat");
             queryModel->setHeaderData(9, Qt::Horizontal, "İndirim");
             queryModel->setHeaderData(10, Qt::Horizontal, "Ödenecek");

             ui->tblProducts->setModel(queryModel);

             ui->twMain->setCurrentIndex(1);
             ui->toolBox->setCurrentIndex(0);
             ui->statusbar->showMessage("Arama yapıldı... " + queryModel->rowCount());
         } else {
             QMessageBox::critical(this, "HATA VAR", "Sorgu yapılamadı...");
             qDebug() << query.lastError();
             return;
         }
     } else {
         QMessageBox::critical(this, "HATA VAR", "Sorgu Çalıştırılamadı");
         qDebug() << query.lastError();
         return;
     }
}


void frmAna::on_btnSearchReset_clicked()
{

    ui->cbSearchByName->setChecked(false);


    ui->txtSearchByName->clear();
    ui->cbSearchByNamePattern->setCurrentIndex(0);


}

void frmAna::on_btnClear_clicked()
{
    QSqlQueryModel * queryModel = new QSqlQueryModel();

    queryModel->setHeaderData(0, Qt::Horizontal, "ID");
    queryModel->setHeaderData(1, Qt::Horizontal, "Okul");
    queryModel->setHeaderData(2, Qt::Horizontal, "Açıklama");
    queryModel->setHeaderData(3, Qt::Horizontal, "Yıl");
    queryModel->setHeaderData(4, Qt::Horizontal, "Kontenjan");
    queryModel->setHeaderData(5, Qt::Horizontal, "Yerleşen");
    queryModel->setHeaderData(6, Qt::Horizontal, "Sıralama");
    queryModel->setHeaderData(7, Qt::Horizontal, "Puan");
    queryModel->setHeaderData(8, Qt::Horizontal, "Fiyat");
    queryModel->setHeaderData(9, Qt::Horizontal, "İndirim");
    queryModel->setHeaderData(10, Qt::Horizontal, "Ödenecek");

    ui->tblProducts->setModel(queryModel);

}



void frmAna::on_cbSearchByName_stateChanged(int arg1)
{
    ui->txtSearchByName->setEnabled(arg1);
    ui->cbSearchByNamePattern->setEnabled(arg1);
}

