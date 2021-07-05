

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
 qDebug() << "1";

    QSize size = qApp->screens()[0]->size();
    this->resize(size*.9);


    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
 qDebug() << "2";
    ui->dteSearchByDateAddMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateAddMax->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateUpdateMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateUpdateMax->setDateTime(QDateTime::currentDateTime());

    ui->tblProducts->setEditTriggers(QAbstractItemView::NoEditTriggers);//
    ui->tblProducts->setSelectionBehavior(QAbstractItemView::SelectRows);//
    ui->tblProducts->setSelectionMode(QAbstractItemView::SingleSelection);//
    ui->tblProducts->resizeColumnsToContents();
    ui->tblProducts->resizeRowsToContents();
    ui->tblProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tblProducts->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Stretch);

 qDebug() << "3";
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
 qDebug() << "4";
    VTKontrolEt::instance()->SetupDB();
 qDebug() << "41";
    if(VTKontrolEt::instance()->Connect()){
       // QTextStream(stdout) << "İlk Bağlantı Açıldı ...";
        qDebug () << "İlk Bağlantı Açıldı ...";
    } else {
        qDebug() << "İlk Bağlantı Açılamadı !!!";
    }

 qDebug() << "5";
    m_frmUrun = new frmUrun(this);
    m_frmGrs = new frmGrs(this);

    bool signalAbout =
            connect(ui->actAbout, SIGNAL(triggered()),
                            this, SLOT(showMenuAbout()));
    Q_ASSERT(signalAbout);
 qDebug() << "6";
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
    QMessageBox::StandardButton mboxSelect = QMessageBox::question( this, "Ürün Takip Yazılımı", "Çıkmak istediğinizden emin misiniz?", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

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
               "Stok Ürün Takip Yazılımı",
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
                qDebug() << "Bağlantı KAPATILDI ...";
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
        qDebug() << "Bağlantı Açık ...";

        LoadProducts();
    } else{
        QMessageBox::critical(this, "HATA VAR Bağlantı KAPALI", VTKontrolEt::instance()->GetError());
        qDebug() << "Bağlantı KAPALI !!!";
    }

    ui->lblAccountInfo->setText(name);
}

void frmAna::LoadProducts(){
    qDebug() << "Ürün listele ";

    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare( "SELECT * FROM product" );

    if (query.exec()){
        if(query.isActive()){
            qDebug() << "Ürün listelemele tamam...";
            queryModel->setQuery(query);

            queryModel->setHeaderData(0, Qt::Horizontal, "ID");
            queryModel->setHeaderData(1, Qt::Horizontal, "Barkod");
            queryModel->setHeaderData(2, Qt::Horizontal, "Ürün Adı");
            queryModel->setHeaderData(3, Qt::Horizontal, "Açıklama");
            queryModel->setHeaderData(4, Qt::Horizontal, "Miktar");
            queryModel->setHeaderData(5, Qt::Horizontal, "Alış Fiyatı");
            queryModel->setHeaderData(6, Qt::Horizontal, "Satış Fiyatı");
            queryModel->setHeaderData(7, Qt::Horizontal, "Ekleme Tarihi");
            queryModel->setHeaderData(8, Qt::Horizontal, "Değiştirme Tarihi");

            ui->tblProducts->setModel(queryModel);
            ui->statusbar->showMessage("Ürün Listeleme tamam ... " + queryModel->rowCount());
        } else {
            QMessageBox::critical(this, "HATA VAR", "Sorgu hatası");
            qDebug() << query.lastError();
            return;
        }
    } else {
        QMessageBox::warning(this, "Ürün", "Ürün listelemede hata !!!");
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
       "WHERE id = :id AND barcode = :barcode"  );

    query.bindValue(":id", index.sibling(index.row(), 0).data().toInt());
    query.bindValue(":barcode", index.sibling(index.row(), 1).data().toString());

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){

                ui->lblProductInfo->setText("Barkod: " +
                    query.value(1).toString() + " - " +
                    index.model()->headerData(index.column(),
                    Qt::Horizontal).toString() + ": " +
                    index.sibling(index.row(),
                    index.column()).data().toString());

                qDebug() << "Ürün bilgisi...: " << query.executedQuery();
            }
        }
    } else {
        QMessageBox::warning(this, "Ürün", "Sorguda Hata...");
        qDebug() << query.lastError();
        return;
    }
}


void frmAna::on_btnSearch_clicked()
{
    QString queryString = "SELECT * FROM product ";
    QString queryStringWhereConcatenator = "WHERE ";

    if(ui->cbSearchByBarkod->checkState())
    {
        QString productBarkod = ui->txtSearchByBarkod->text().trimmed();
        if(!productBarkod.isEmpty() && productBarkod.length() > 0)
        {
            queryString += queryStringWhereConcatenator;
            queryString += "barcode = '" + productBarkod + "' ";
        }

        else
        {
            QMessageBox::warning(this, "Arama", "Barkod ile aramak için barkod giriniz ...");
            return;
        }
    }

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
            QMessageBox::warning(this, "Arama", "Ürün adı ile aramak için ürün adı giriniz ...");
            return;
        }
    }




    if(ui->cbSearchByDate->checkState()){
        QString time_format = "yyyy-MM-dd  HH:mm:ss";

        if(ui->cbSearchByDateAdd->checkState()){
            QDateTimeEdit* min = ui->dteSearchByDateAddMin;
            QDateTimeEdit* max = ui->dteSearchByDateAddMax;

            QString smin = min->dateTime().toString(time_format);
            QString smax = max->dateTime().toString(time_format);

            queryString += queryStringWhereConcatenator;
            queryString += "dateAdd BETWEEN = " + smin + " AND " + smax + " ";
            queryStringWhereConcatenator = "AND ";
        }
        if(ui->cbSearchByDateUpdate->checkState()){
            QDateTimeEdit* min = ui->dteSearchByDateUpdateMin;
            QDateTimeEdit* max = ui->dteSearchByDateUpdateMax;

            QString smin = min->dateTime().toString(time_format);
            QString smax = max->dateTime().toString(time_format);

            queryString += queryStringWhereConcatenator;
            queryString += "dateUpdate BETWEEN '" + smin + "' AND '" + smax + "' ";
            queryStringWhereConcatenator = "AND ";
        }
    }

    if(ui->cbSearchByQuantity->checkState()){
        if(ui->sbSearchByQuantity->value() > 0){
            queryString += queryStringWhereConcatenator;
            if(ui->cbSearchByQuantityPattern->currentIndex() == 0){ //LOWER
                queryString += "quantity <= " + QString::number(ui->sbSearchByQuantity->value()) + " ";
            }else if(ui->cbSearchByQuantityPattern->currentIndex() == 1){ //HIGHER
                queryString += "quantity >= " + QString::number(ui->sbSearchByQuantity->value()) + " ";
            }
            queryStringWhereConcatenator = "AND ";
        }else{
            QMessageBox::warning(this, "Arama", "Miktar ile arama yaparken 0 'dan büyük miktar giriniz...");
            return;
        }

    }

    if(ui->cbSearchByPrice->checkState()){
        if(ui->cbSearchByPricePurchase->checkState()){
            if(ui->dsbSearchByPricePurchase->value() > 0.0){
                queryString += queryStringWhereConcatenator;
                if(ui->cbSearchByPricePurchasePattern->currentIndex() == 0){ //LOWER
                    queryString += "purchasePrice <= " + QString::number(ui->dsbSearchByPricePurchase->value()) + " ";
                }else if(ui->cbSearchByPricePurchasePattern->currentIndex() == 1){ //HIGHER
                    queryString += "purchasePrice >= " + QString::number(ui->dsbSearchByPricePurchase->value()) + " ";
                }
                queryStringWhereConcatenator = "AND ";
            }else{
                QMessageBox::warning(this, "Arama", "0 TL den büyük fiyat giriniz...");
                return;
            }

        }
        if(ui->cbSearchByPriceSale->checkState()){
            if(ui->dsbSearchByPriceSale->value() > 0.0){
                queryString += queryStringWhereConcatenator;
                if(ui->cbSearchByPriceSalePattern->currentIndex() == 0){ //LOWER
                    queryString += "salePrice <= " + QString::number(ui->dsbSearchByPriceSale->value()) + " ";
                }else if(ui->cbSearchByPriceSalePattern->currentIndex() == 1){ //HIGHER
                    queryString += "salePrice >= " + QString::number(ui->dsbSearchByPriceSale->value()) + " ";
                }
                queryStringWhereConcatenator = "AND ";
            }else{
                QMessageBox::warning(this, "Arama", "Satı fiyatını 0 TL den büyük fiyat giriniz...");
                return;
            }
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
             queryModel->setHeaderData(1, Qt::Horizontal, "Barkod");
             queryModel->setHeaderData(2, Qt::Horizontal, "Ürün");
             queryModel->setHeaderData(3, Qt::Horizontal, "Açıklama");
             queryModel->setHeaderData(4, Qt::Horizontal, "Adet");
             queryModel->setHeaderData(5, Qt::Horizontal, "Alış Fiyatı");
             queryModel->setHeaderData(6, Qt::Horizontal, "Satış Fiyatı");
             queryModel->setHeaderData(7, Qt::Horizontal, "Eklenme Tarihi");
             queryModel->setHeaderData(8, Qt::Horizontal, "Güncelleme Tarihi");

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
    ui->cbSearchByBarkod->setChecked(false);
    ui->cbSearchByName->setChecked(false);
    ui->cbSearchByDate->setChecked(false);
    ui->cbSearchByDateAdd->setChecked(false);
    ui->cbSearchByDateUpdate->setChecked(false);
    ui->cbSearchByQuantity->setChecked(false);
    ui->cbSearchByPrice->setChecked(false);
    ui->cbSearchByPricePurchase->setChecked(false);
    ui->cbSearchByPriceSale->setChecked(false);

    ui->txtSearchByBarkod->clear();

    ui->txtSearchByName->clear();
    ui->cbSearchByNamePattern->setCurrentIndex(0);

    ui->dteSearchByDateAddMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateAddMax->setDateTime(QDateTime::currentDateTime());

    ui->dteSearchByDateUpdateMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateUpdateMax->setDateTime(QDateTime::currentDateTime());

    ui->sbSearchByQuantity->setValue(0);
    ui->cbSearchByQuantityPattern->setCurrentIndex(0);

    ui->dsbSearchByPricePurchase->setValue(0.0);
    ui->cbSearchByPricePurchasePattern->setCurrentIndex(0);

    ui->dsbSearchByPriceSale->setValue(0.0);
    ui->cbSearchByPriceSalePattern->setCurrentIndex(0);
}

void frmAna::on_btnClear_clicked()
{
    QSqlQueryModel * queryModel = new QSqlQueryModel();
    queryModel->setHeaderData(0, Qt::Horizontal, "ID");
    queryModel->setHeaderData(1, Qt::Horizontal, "Barkod");
    queryModel->setHeaderData(2, Qt::Horizontal, "Ürün");
    queryModel->setHeaderData(3, Qt::Horizontal, "Açıklama");
    queryModel->setHeaderData(4, Qt::Horizontal, "Adet");
    queryModel->setHeaderData(5, Qt::Horizontal, "Alış Fiyatı");
    queryModel->setHeaderData(6, Qt::Horizontal, "Satış Fiyatı");
    queryModel->setHeaderData(7, Qt::Horizontal, "Eklenme Tarihi");
    queryModel->setHeaderData(8, Qt::Horizontal, "Güncelleme Tarihi");
    ui->tblProducts->setModel(queryModel);

}

void frmAna::on_cbSearchByBarkod_stateChanged(int arg1)
{
    ui->txtSearchByBarkod->setEnabled(arg1);
}


void frmAna::on_cbSearchByName_stateChanged(int arg1)
{
    ui->txtSearchByName->setEnabled(arg1);
    ui->cbSearchByNamePattern->setEnabled(arg1);
}

void frmAna::on_cbSearchByDate_stateChanged(int arg1)
{
    ui->cbSearchByDateAdd->setEnabled(arg1);
    ui->cbSearchByDateUpdate->setEnabled(arg1);
    if(!arg1){
        ui->dteSearchByDateAddMin->setEnabled(arg1);
        ui->dteSearchByDateAddMax->setEnabled(arg1);

        ui->dteSearchByDateUpdateMin->setEnabled(arg1);
        ui->dteSearchByDateUpdateMax->setEnabled(arg1);
    }else{
        ui->dteSearchByDateAddMin->setEnabled(ui->cbSearchByDateAdd->checkState());
        ui->dteSearchByDateAddMax->setEnabled(ui->cbSearchByDateAdd->checkState());

        ui->dteSearchByDateUpdateMin->setEnabled(ui->cbSearchByDateUpdate->checkState());
        ui->dteSearchByDateUpdateMax->setEnabled(ui->cbSearchByDateUpdate->checkState());
    }
}

void frmAna::on_cbSearchByDateAdd_stateChanged(int arg1)
{
    ui->dteSearchByDateAddMin->setEnabled(arg1);
    ui->dteSearchByDateAddMax->setEnabled(arg1);
}

void frmAna::on_cbSearchByDateUpdate_stateChanged(int arg1)
{
    ui->dteSearchByDateUpdateMin->setEnabled(arg1);
    ui->dteSearchByDateUpdateMax->setEnabled(arg1);
}

void frmAna::on_cbSearchByQuantity_stateChanged(int arg1)
{
    ui->sbSearchByQuantity->setEnabled(arg1);
    ui->cbSearchByQuantityPattern->setEnabled(arg1);
}

void frmAna::on_cbSearchByPrice_stateChanged(int arg1)
{
    ui->cbSearchByPricePurchase->setEnabled(arg1);
    ui->cbSearchByPriceSale->setEnabled(arg1);
    if(!arg1){
        ui->dsbSearchByPricePurchase->setEnabled(arg1);
        ui->cbSearchByPricePurchasePattern->setEnabled(arg1);

        ui->dsbSearchByPriceSale->setEnabled(arg1);
        ui->cbSearchByPriceSalePattern->setEnabled(arg1);
    }else{
        ui->dsbSearchByPricePurchase->setEnabled(ui->cbSearchByPricePurchase->checkState());
        ui->cbSearchByPricePurchasePattern->setEnabled(ui->cbSearchByPricePurchase->checkState());

        ui->dsbSearchByPriceSale->setEnabled(ui->cbSearchByPriceSale->checkState());
        ui->cbSearchByPriceSalePattern->setEnabled(ui->cbSearchByPriceSale->checkState());
    }
}

void frmAna::on_cbSearchByPricePurchase_stateChanged(int arg1)
{
    ui->dsbSearchByPricePurchase->setEnabled(arg1);
    ui->cbSearchByPricePurchasePattern->setEnabled(arg1);
}

void frmAna::on_cbSearchByPriceSale_stateChanged(int arg1)
{
    ui->dsbSearchByPriceSale->setEnabled(arg1);
    ui->cbSearchByPriceSalePattern->setEnabled(arg1);
}
