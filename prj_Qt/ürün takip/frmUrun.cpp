#include "frmUrun.h"
#include "ui_frmUrun.h"
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include <QScreen>

#include "frmAna.h"
#include "VTKontrol.h"

frmUrun::frmUrun(QWidget *parent) :
    QDialog(parent), ui(new Ui::frmUrun)

{
    ui->setupUi(this);


    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
///
    DbProduct();
    LoadProductsToComboBox();

    ui->dteAdd->setDateTime(QDateTime::currentDateTime());
    ui->dteUpdate->setDateTime(QDateTime::currentDateTime());

    this->Clear();

}

frmUrun::~frmUrun()
{
    delete ui;
}


void frmUrun::Clear(){
    ui->txtBarcode->clear();
    ui->txtName->clear();
    ui->txtDescription->clear();
    ui->sbQuantity->clear();
    ui->sbPurchasePrice->clear();
    ui->sbSalePrice->clear();
    ui->cbReadonly->setChecked(false);
}

bool frmUrun::CheckInputs(){
    bool flag = true;

    if (ui->txtBarcode->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ürün", "Barkod numarası boş bırakılamaz!");
        flag = false;
    } else if (ui->txtBarcode->text().trimmed().length() != 11) {
        QMessageBox::warning(this, "Ürün", "Barkod numarası 11 haneli olmalıdır!");
        flag = false;
    } else if (ui->txtName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ürün", "Ürün ismi boş bırakılamaz!");
        flag = false;
    } else if (ui->txtDescription->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ürün", "Ürün açıklaması boş bırakılamaz!");
        flag = false;
    } else if (ui->sbQuantity->value() <= 0.0) {
        QMessageBox::warning(this, "Ürün", "Ürün miktarını doğru şekilde giriniz!");
        flag = false;
    } else if (ui->sbPurchasePrice->value() <= 0.0) {
        QMessageBox::warning(this, "Ürün", "Ürün satın alma fiyatını doğru şekilde giriniz!");
        flag = false;
    } else if (ui->sbSalePrice->value() <= 0.0) {
        QMessageBox::warning(this, "Ürün", "Ürün satış fiyatını doğru şekilde giriniz!");
        flag = false;
    }

    return flag;
}

void frmUrun::on_btnAdd_clicked()
{
    QString barcode = ui->txtBarcode->text().trimmed();
    QString name = ui->txtName->text().trimmed();
    QString description = ui->txtDescription->toPlainText().trimmed();

    if(this->CheckInputs()){
        if(VTKontrolEt::instance()->IsOpen()){

            QSqlQuery query;




            query.prepare(
                        "INSERT INTO "
                        "product "
                        "(barcode, name, description, quantity, "
                        "purchasePrice, salePrice, dateAdd, dateUpdate) "
                        "VALUES "
                        "(:barcode, :name, :description, :quantity, "
                        ":purchasePrice, :salePrice, :dateAdd, :dateUpdate)"
                        );

            query.bindValue(":barcode", barcode);
            query.bindValue(":name", name);
            query.bindValue(":description", description);

            query.bindValue(":quantity", ui->sbQuantity->value());
            query.bindValue(":purchasePrice", ui->sbPurchasePrice->value());
            query.bindValue(":salePrice", ui->sbSalePrice->value());
            query.bindValue(":dateAdd", ui->dteAdd->text()  );
            query.bindValue(":dateUpdate",ui->dteUpdate->text() );


            if(query.exec()){
                if(query.isActive()){
                    this->Clear();
                    this->Refresh();
                    ui->cbID->addItem(barcode);
                    QMessageBox::information(this, "Ürün", "Ürün başarıyla eklendi!");
                    qDebug() << "Database query OK.";
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ürün", "Ürün eklenirken bir hata oluştu!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Ürün", "Veritabanı bağlantısı kapalı!");
            qDebug() << "Database connection closed.";
            return;
        }
    }
}

void frmUrun::on_btnUpdate_clicked()
{
    QString barcode = ui->txtBarcode->text().trimmed();
    QString name = ui->txtName->text().trimmed();
    QString description = ui->txtDescription->toPlainText().trimmed();

    if(QString::compare(barcode, ui->cbID->currentText(), Qt::CaseSensitive) != 0){
        QMessageBox::warning(this, "Ürün", "Güncellenmek istenen ürünün barkodu değiştirilemez!");
        ui->txtBarcode->setText(ui->cbID->currentText());
        return;
    }

    if(this->CheckInputs()){
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Ürün", "Ürünü güncellemek istediğinizden emin misiniz?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No) {
            return;
        } else if (reply == QMessageBox::Yes){
            if(VTKontrolEt::instance()->IsOpen()){

                QSqlQuery query;

                query.prepare(
                            "UPDATE "
                            "product "
                            "SET name = :name, description = :description , quantity = :quantity, purchasePrice = :purchasePrice, salePrice = :salePrice, dateUpdate = NOW() "
                            "WHERE barcode = :barcode"
                            );

                query.bindValue(":barcode", ui->cbID->currentText());
                query.bindValue(":name", name);
                query.bindValue(":description", description);
                query.bindValue(":quantity", ui->sbQuantity->value());
                query.bindValue(":purchasePrice", ui->sbPurchasePrice->value());
                query.bindValue(":salePrice", ui->sbSalePrice->value());

                if(query.exec()){
                    if(query.isActive()){
                        if(query.numRowsAffected() <= 0){
                            QMessageBox::warning(this, "Ürün", "Hata !!!");
                            qDebug() << query.lastError();
                            return;
                        }
                        this->Refresh();
                        this->LoadProduct(ui->cbID->currentText());
                        QMessageBox::information(this, "Ürün", "Ürün güncellenmesi sağlandı...");
                        qDebug() << "Database query OK.";
                        return;
                    }
                } else {
                    QMessageBox::warning(this, "Ürün", "Ürün güncellemede HATA !!!");
                    qDebug() << query.lastError();
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ürün", "Veritabanı bağlantısı sağlanamdı !!!");
                qDebug() << "Veritabanı bağlantısı sağlanamdı !!!";
                return;
            }
        }
    }
}

void frmUrun::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Ürün", "Ürünü silmeyi onaylayın ... ", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    } else if (reply == QMessageBox::Yes){
        if(VTKontrolEt::instance()->IsOpen()){

            QSqlQuery query;

            query.prepare(
                        "DELETE FROM "
                        "product "
                        "WHERE "
                        "barcode = :barcode"
                        );

            query.bindValue(":barcode", ui->cbID->currentText());

            if(query.exec()){
                if(query.isActive()){
                    if(query.numRowsAffected() <= 0){
                        QMessageBox::warning(this, "Ürün", "BARKOD hatası!");
                        qDebug() << query.lastError();
                        return;
                    }
                    this->Clear();
                    this->Refresh();
                    QMessageBox::information(this, "Ürün", "Ürün silindi!");
                    qDebug() << "Veritabanı sorgulama tamam ...";
                    qDebug() << "Silinen Ürün......: " << ui->cbID->currentText();
                    ui->cbID->removeItem(ui->cbID->currentIndex());
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ürün", "Silme hatası !!!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Ürün", "Veritabanı bağlantısı sağlanamadı !!!");
            qDebug() << "Veritabanı bağlantısı sağlanamadı !!!";
            return;
        }
    }
}

void frmUrun::LoadProductsToComboBox(){

    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;
    query.exec("SELECT * FROM Product ORDER BY dateAdd");

    while (query.next()) {
        if(query.isActive()){
            int id = query.value(0).toInt();
            QString barcode = query.value(1).toString();


            ui->cbID->addItem(barcode);
        }
    }
}

void frmUrun::LoadProduct(const int index){
    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    DbProduct();


    query.prepare(
                "SELECT * FROM "
                "product "
                "ORDER BY "
                "ID "
                "LIMIT "
                ":index, 1"
                );

    query.bindValue(":index", index);

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){
                ui->cbReadonly->setChecked(true);
                ui->cbID->setCurrentIndex(index);
                ui->txtBarcode->setText(query.value(1).toString());
                ui->txtName->setText(query.value(2).toString());
                ui->txtDescription->setText(query.value(3).toString());
                ui->sbQuantity->setValue(query.value(4).toInt());
                ui->sbPurchasePrice->setValue(query.value(5).toDouble());
                ui->sbSalePrice->setValue(query.value(6).toDouble());
                ui->dteAdd->setDateTime(query.value(7).toDateTime());
                ui->dteUpdate->setDateTime(query.value(8).toDateTime());
                qDebug() << "Ürün Listeleme...: " << index;
            }
        }
    } else {
        QMessageBox::warning(this, "Ürün", "HATA !!! ");
        qDebug() << query.lastError();
        return;
    }
}
//////////////////////////////////////////////
void frmUrun::DbProduct()
{
    //////////////////////
    QSqlQuery q;
    QString ct = "CREATE TABLE IF NOT EXISTS product ("
                 "id            integer primary key,"
                 "barcode       text    ,"
                 "name          text    ,"
                 "description   text    ,"
                 "quantity      integer ,"
                 "purchasePrice real    ,"
                 "salePrice     real    ,"
                 "dateAdd       text DEFAULT CURRENT_TIMESTAMP,"
                 "dateUpdate    text DEFAULT CURRENT_TIMESTAMP)" ;

            if (!q.exec( ct ))
            {
                qDebug() << "  'product' Dosyası Oluşturulamadı - "
                     << q.lastError() ;
            }
            else
                qDebug() << "  'product' Dosyası Oluşturuldu - ";



    ct = "  CREATE TABLE IF NOT EXISTS recipt ("
         "id  integer primary key,"
         "sale_id integer,"
         "seller_id integer,"
         "buyer_id integer,"
         "date text )" ;

                if (!q.exec( ct ))
                {
                    qDebug() << "  'recipt' Dosyası Oluşturulamadı - "
                         << q.lastError() ;
                }
                else
                    qDebug() << "  'recipt' Dosyası Oluşturuldu - ";


    ct = "CREATE TABLE IF NOT EXISTS refund  ("
         "id        integer primary key,"
         "s_id      integer ,   "
         "description text, "
         "date  text )" ;

                if (!q.exec( ct ))
                {
                    qDebug() << "  'refund' Dosyası Oluşturulamadı - "
                         << q.lastError() ;
                }
                else
                    qDebug() << "  'refund' Dosyası Oluşturuldu - ";


    ct = "CREATE TABLE IF NOT EXISTS sale ("
         "id         integer primary key, "
         "p_id       integer ,"
         "decription text,"
         "date       text )" ;

                if (!q.exec( ct ))
                {
                    qDebug() << "  'sale' Dosyası Oluşturulamadı - "
                         << q.lastError() ;
                }
                else
                    qDebug() << "  'sale' Dosyası Oluşturuldu - ";


    ct = " CREATE TABLE IF NOT EXISTS stock  ("
         "id     integer primary key,"
         "name   text   ,"
         "type   text   )" ;


                if (!q.exec( ct ))
                {
                    qDebug() << "  'stock' Dosyası Oluşturulamadı - "
                         << q.lastError() ;
                }
                else
                    qDebug() << "  'stock' Dosyası Oluşturuldu - ";






            /////////////////////////////

}
///////////////////////////////////////////////
void frmUrun::LoadProduct(const QString barcode){
    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare(
                "SELECT * FROM "
                "product "
                "WHERE "
                "barcode = :barcode"
                );

    query.bindValue(":barcode", barcode);

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){
                ui->txtBarcode->setText(query.value(1).toString());
                ui->txtName->setText(query.value(2).toString());
                ui->txtDescription->setText(query.value(3).toString());
                ui->sbQuantity->setValue(query.value(4).toInt());
                ui->sbPurchasePrice->setValue(query.value(5).toDouble());
                ui->sbSalePrice->setValue(query.value(6).toDouble());
                ui->dteAdd->setDateTime(query.value(7).toDateTime());
                ui->dteUpdate->setDateTime(query.value(8).toDateTime());
                qDebug() << "Ürün yükleme....: " << barcode;
            }
        }
    } else {
        QMessageBox::warning(this, "Ürün", "HATA !!!");
        qDebug() << query.lastError();
        return;
    }
}

void frmUrun::on_cbID_activated(int index)
{
    LoadProduct(ui->cbID->currentText());
}

void frmUrun::on_cbReadonly_stateChanged(int arg1)
{
    ui->txtBarcode->setReadOnly(m_isReadonly);
    ui->txtName->setReadOnly(m_isReadonly);
    ui->txtDescription->setReadOnly(m_isReadonly);
    ui->sbQuantity->setReadOnly(m_isReadonly);
    ui->sbPurchasePrice->setReadOnly(m_isReadonly);
    ui->sbSalePrice->setReadOnly(m_isReadonly);

    m_isReadonly = !m_isReadonly;
}
