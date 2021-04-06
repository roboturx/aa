#include "frmUrun.h"
#include "ui_frmUrun.h"
#include <QMessageBox>
#include <QStyle>
//#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include <QScreen>

#include "frmAna.h"
#include "VTKontrol.h"

frmUrun::frmUrun(QWidget *parent) : QDialog(parent), ui(new Ui::frmUrun) {
    ui->setupUi(this);


    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
///
    DbProduct();
    LoadProductsToComboBox();

  //  ui->dteAdd->setDateTime(QDateTime::currentDateTime());
  //  ui->dteUpdate->setDateTime(QDateTime::currentDateTime());

    this->Clear();

}

frmUrun::~frmUrun()
{
    delete ui;
}


void frmUrun::Clear(){

    ui->txtName->clear();
    ui->txtDescription->clear();
    ui->yil->clear();
    ui->kontenjan->clear();
    ui->yerlesen->clear();
    ui->siralama->clear();
    ui->puan->clear();
    ui->fiyat->clear();
    ui->indirim->clear();
    ui->odeme->clear();
    ui->cbReadonly->setChecked(false);
}

bool frmUrun::CheckInputs(){
    bool flag = true;
/*
    if (ui->txtBarcode->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Okul", "Barkod numarası boş bırakılamaz!");
        flag = false;
    } else if (ui->txtBarcode->text().trimmed().length() != 11) {
        QMessageBox::warning(this, "Okul", "Barkod numarası 11 haneli olmalıdır!");
        flag = false;
    } else if (ui->txtName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Okul", "Okul ismi boş bırakılamaz!");
        flag = false;
    } else if (ui->txtDescription->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Okul", "Okul açıklaması boş bırakılamaz!");
        flag = false;
    } else if (ui->sbQuantity->value() <= 0.0) {
        QMessageBox::warning(this, "Okul", "Okul miktarını doğru şekilde giriniz!");
        flag = false;
    } else if (ui->sbPurchasePrice->value() <= 0.0) {
        QMessageBox::warning(this, "Okul", "Okul satın alma fiyatını doğru şekilde giriniz!");
        flag = false;
    } else if (ui->sbSalePrice->value() <= 0.0) {
        QMessageBox::warning(this, "Okul", "Okul satış fiyatını doğru şekilde giriniz!");
        flag = false;
    }
*/
    return flag;
}

void frmUrun::on_btnAdd_clicked()
{

    QString name = ui->txtName->text().trimmed();
    QString description = ui->txtDescription->text().trimmed() ;

    if(this->CheckInputs()){
        if(VTKontrolEt::instance()->IsOpen()){

            QSqlQuery query;




            query.prepare(
                        "INSERT INTO "
                        "product "
                        "(name, description, yil, "
                        "kontenjan, yerlesen,siralama,puan,"
                        "fiyat,indirim,odeme ) "
                        "VALUES "
                        "(:name, :description, :yil, "
                        ":kontenjan, :yerlesen, :siralama, :puan,"
                        ":fiyat, :indirim, :odeme)"
                        );

            query.bindValue(":name", name);
            query.bindValue(":description", description);
            query.bindValue(":yil", ui->yil->text());

            query.bindValue(":kontenjan", ui->kontenjan->text());
            query.bindValue(":yerlesen", ui->yerlesen->text());
            query.bindValue(":siralama", ui->siralama->text()  );
            query.bindValue(":puan",ui->puan->text() );

            query.bindValue(":fiyat",ui->fiyat->text() );
            query.bindValue(":indirim",ui->indirim->text() );
            query.bindValue(":odeme",ui->odeme->text() );


            if(query.exec()){
                if(query.isActive()){
                    this->Clear();
                    this->Refresh();
                    ui->cbID->addItem(name);
                    QMessageBox::information(this, "Okul", "Okul başarıyla eklendi!");
                    qDebug() << "Database query OK.";
                    return;
                }
            } else {
                QMessageBox::warning(this, "Okul", "Okul eklenirken bir hata oluştu!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Okul", "Veritabanı bağlantısı kapalı!");
            qDebug() << "Database connection closed.";
            return;
        }
    }
}

void frmUrun::on_btnCopy_clicked()
{

    QString name = ui->txtName->text().trimmed() + "  01";
    QString description = ui->txtDescription->text().trimmed() ;

    if(this->CheckInputs()){
        if(VTKontrolEt::instance()->IsOpen()){

            QSqlQuery query;




            query.prepare(
                        "INSERT INTO "
                        "product "
                        "(name, description, yil, "
                        "kontenjan, yerlesen,siralama,puan,"
                        "fiyat,indirim,odeme ) "
                        "VALUES "
                        "(:name, :description, :yil, "
                        ":kontenjan, :yerlesen, :siralama, :puan,"
                        ":fiyat, :indirim, :odeme)"
                        );

            query.bindValue(":name", name);
            query.bindValue(":description", description);
            query.bindValue(":yil", ui->yil->text());

            query.bindValue(":kontenjan", ui->kontenjan->text());
            query.bindValue(":yerlesen", ui->yerlesen->text());
            query.bindValue(":siralama", ui->siralama->text()  );
            query.bindValue(":puan",ui->puan->text() );

            query.bindValue(":fiyat",ui->fiyat->text() );
            query.bindValue(":indirim",ui->indirim->text() );
            query.bindValue(":odeme",ui->odeme->text() );


            if(query.exec()){
                if(query.isActive()){
                 // this->Clear();
                    this->Refresh();
                    ui->cbID->addItem(name);
                    QMessageBox::information(this, "Okul", "Okul başarıyla eklendi!");
                    qDebug() << "Database query OK.";
                    return;
                }
            } else {
                QMessageBox::warning(this, "Okul", "Okul eklenirken bir hata oluştu!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Okul", "Veritabanı bağlantısı kapalı!");
            qDebug() << "Database connection closed.";
            return;
        }
    }



}

void frmUrun::on_btnUpdate_clicked()
{
    //QString barcode = ui->txtBarcode->text().trimmed();
    QString name = ui->txtName->text().trimmed();
    QString description = ui->txtDescription->text().trimmed() ;

    /*if(QString::compare(name, ui->cbID->currentText(), Qt::CaseSensitive) != 0){
        QMessageBox::warning(this, "Okul", "Güncellenmek istenen okulun adı değiştirilemez!");
        ui->txtName->setText(ui->cbID->currentText());
        return;
    }*/

    if(this->CheckInputs()){
        QMessageBox::StandardButton reply =
                QMessageBox::question(this, "Okul",
                "Okulü güncellemek istediğinizden emin misiniz?",
                QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No) {
            return;
        } else if (reply == QMessageBox::Yes){
            if(VTKontrolEt::instance()->IsOpen()){

                QSqlQuery query;

                query.prepare(
                            "UPDATE "
                            "product "
                            "SET name = :name, description = :description , "
                            "yil = :yil, kontenjan = :kontenjan, "
                            "yerlesen = :yerlesen, siralama = :siralama,"
                            "puan = :puan , fiyat = :fiyat , "
                            "indirim = :indirim, odeme = :odeme "
                            "WHERE name = :name"
                            );

                query.bindValue(":name", ui->txtName->text());
                query.bindValue(":description", ui->txtDescription->text());
                query.bindValue(":yil", ui->yil->value());
                query.bindValue(":kontenjan", ui->kontenjan->value());
                query.bindValue(":yerlesen", ui->yerlesen->value());
                query.bindValue(":siralama", ui->siralama->value());
                query.bindValue(":puan", ui->puan->value());
                query.bindValue(":fiyat", ui->fiyat->value());
                query.bindValue(":indirim", ui->indirim->value());
                query.bindValue(":odeme", ui->odeme->value());


                if(query.exec()){
                    if(query.isActive()){
                       /* if(query.numRowsAffected() <= 0){
                            QMessageBox::warning(this, "Okul", "Hata 222 !!!");
                            qDebug() << query.lastError();
                            return;
                        }*/
                        this->Refresh();
                        this->LoadProduct(ui->cbID->currentText());
                        QMessageBox::information(this, "Okul",
                             "Okul güncellenmesi sağlandı...");
                        qDebug() << "Database query OK.";
                        return;
                    }
                } else {
                    QMessageBox::warning(this, "Okul",
                           "Okul güncellemede HATA !!!");
                    qDebug() << query.lastError();
                    return;
                }
            } else {
                QMessageBox::warning(this, "Okul", "Veritabanı bağlantısı sağlanamdı !!!");
                qDebug() << "Veritabanı bağlantısı sağlanamdı !!!";
                return;
            }
        }
    }
}

void frmUrun::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Okul", "Okulü silmeyi onaylayın ... ", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    } else if (reply == QMessageBox::Yes){
        if(VTKontrolEt::instance()->IsOpen()){

            QSqlQuery query;

            query.prepare(
                        "DELETE FROM "
                        "product "
                        "WHERE "
                        "name = :name"
                        );

            query.bindValue(":name", ui->cbID->currentText());

            if(query.exec()){
                if(query.isActive()){
                    if(query.numRowsAffected() <= 0){
                        QMessageBox::warning(this, "okul", "okul hatası!");
                        qDebug() << query.lastError();
                        return;
                    }
                    this->Clear();
                    this->Refresh();
                    QMessageBox::information(this, "okul", "okul silindi!");
                    qDebug() << "Veritabanı sorgulama tamam ...";
                    qDebug() << "Silinen okul......: " << ui->cbID->currentText();
                    ui->cbID->removeItem(ui->cbID->currentIndex());
                    return;
                }
            } else {
                QMessageBox::warning(this, "Okul", "Silme hatası !!!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Okul", "Veritabanı bağlantısı sağlanamadı !!!");
            qDebug() << "Veritabanı bağlantısı sağlanamadı !!!";
            return;
        }
    }
}

void frmUrun::LoadProductsToComboBox(){

    //QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;
    query.exec("SELECT * FROM Product ORDER BY name");

    while (query.next()) {
        if(query.isActive()){
            //int id = query.value(0).toInt();
            QString barcode = query.value(1).toString();


            ui->cbID->addItem(barcode);
        }
    }
}

void frmUrun::LoadProduct(const int index){
    //QSqlQueryModel * queryModel = new QSqlQueryModel();

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
             //   ui->txtBarcode->setText(query.value(1).toString());
                ui->txtName->setText(query.value(1).toString());
                ui->txtDescription->setText(query.value(2).toString());
                ui->yil->setValue(query.value(3).toInt());
                ui->kontenjan->setValue(query.value(4).toInt());
                ui->yerlesen->setValue(query.value(5).toInt());
                ui->siralama->setValue(query.value(6).toInt());
                ui->puan->setValue(query.value(7).toDouble());
                ui->fiyat->setValue(query.value(7).toInt());
                ui->indirim->setValue(query.value(7).toInt());
                ui->odeme->setValue(query.value(7).toInt());

                qDebug() << "Okul Listeleme...: " << index;
            }
        }
    } else {
        QMessageBox::warning(this, "Okul", "HATA !!! ");
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

                 "name          text    ," // okul
                 "description   text    ," // açıkl
                 "yil           integer ," // yil     yil
                 "kontenjan     integer ," //kont
                 "yerlesen      integer ," // yerl
                 "siralama      integer ," // sıra
                 "puan          real    ," // puan
                 "fiyat         integer ," // fiat
                 "indirim       integer ," // ind
                 "odeme         integer )" ; // ödeme

            if (!q.exec( ct ))
            {
                qDebug() << "  'product' Dosyası Oluşturulamadı - "
                     << q.lastError() ;
            }
            else
                qDebug() << "  'product' Dosyası Oluşturuldu - ";


}
///////////////////////////////////////////////
void frmUrun::LoadProduct(const QString barcode){
    //QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare(
                "SELECT * FROM "
                "product "
                "WHERE "
                "name = :name"
                );

    query.bindValue(":name", barcode);

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){

                ui->txtName->setText(query.value(1).toString());
                ui->txtDescription->setText(query.value(2).toString());
                ui->yil->setValue(query.value(3).toInt());
                ui->kontenjan->setValue(query.value(4).toInt());
                ui->yerlesen->setValue(query.value(5).toInt());
                ui->siralama->setValue(query.value(6).toInt());
                ui->puan->setValue(query.value(7).toDouble());
                ui->fiyat->setValue(query.value(8).toInt());
                ui->indirim->setValue(query.value(9).toInt());
                ui->odeme->setValue(query.value(10).toInt());
                qDebug() << "Okul yükleme....: " << barcode;
            }
        }
    } else {
        QMessageBox::warning(this, "Okul", "HATA !!!");
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

    ui->txtName->setReadOnly(m_isReadonly);
    ui->txtDescription->setReadOnly(m_isReadonly);
    ui->yil->setReadOnly(m_isReadonly);
    ui->kontenjan->setReadOnly(m_isReadonly);
    ui->yerlesen->setReadOnly(m_isReadonly);
    ui->siralama->setReadOnly(m_isReadonly);
    ui->puan->setReadOnly(m_isReadonly);
    ui->fiyat->setReadOnly(m_isReadonly);
    ui->indirim->setReadOnly(m_isReadonly);
    ui->odeme->setReadOnly(m_isReadonly);


    m_isReadonly = !m_isReadonly;
}
