#include "frmKyt.h"
#include "ui_frmKyt.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QLabel>
#include <QDebug>
#include <QSqlError>
#include <QRegExp>

#include "VTKontrol.h"

frmKyt::frmKyt(QWidget *parent) : QDialog(parent), ui(new Ui::frmKyt) {
    ui->setupUi(this);

    this->setFixedSize(this->maximumSize());
    this->setWindowTitle("Kullanıcı Kayıt Bilgileri Girişi");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

frmKyt::~frmKyt()
{
    this->setFixedSize(this->width(),this->height());
    delete ui;
}

bool frmKyt::CheckInputs(){
    QString name = ui->txtName->text().trimmed();
    QString surname = ui->txtSurname->text().trimmed();
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text().trimmed();
    QString password2 = ui->txtPassword2->text().trimmed();
    QString mailAddress = ui->txtMail->text().trimmed();
    QString mobilePhone = ui->txtPhoneNumber->text().trimmed();
    QString homeAddress = ui->txtAddress->toPlainText().trimmed();

    bool flag = true;

    QRegExp regexMail("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    regexMail.setCaseSensitivity(Qt::CaseInsensitive);
    regexMail.setPatternSyntax(QRegExp::RegExp);

    //QRegExp regexPhone("^[0-9]{10}$");
    QRegExp regexPhone("0\\d\\d\\d\\d\\d\\d\\d\\d\\d\\d");

    regexPhone.setCaseSensitivity(Qt::CaseInsensitive);
    regexPhone.setPatternSyntax(QRegExp::RegExp);

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "İsim giriniz...");
        flag = false;
    } else if (surname.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Soyad giriniz...");
        flag = false;
    } else if (username.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Kullanıcı adı giriniz...");
        flag = false;
    } else if (password.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Şifre giriniz...");
        flag = false;
    } else if (password2.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Şifreyi tekrar giriniz...");
        flag = false;
    } else if (QString::compare(password, password2, Qt::CaseSensitive) != 0) {
        QMessageBox::warning(this, "Kayıt", "Şifreleriz eşleşmiyor...");
        flag = false;
    } else if (mailAddress.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "e-posta giriniz...(abc@def.com gibi)");
        flag = false;
    /* }

   else if (!regexMail.exactMatch(mailAddress)) {
        QMessageBox::warning(this, "Kayıt", "Lütfen mail adresinizi doğru şekilde giriniz!");
        flag = false;*/
    } else if (mobilePhone.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Telefon giriniz (5053202240 gibi)...");
        flag = false;
   /* } else if (!regexPhone.exactMatch(mobilePhone)) {
        QMessageBox::warning(this, "Kayıt", "Lütfen telefon numaranızı doğru şekilde ve 11 hane olarak giriniz!");
        flag = false;*/
    } else if (homeAddress.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Adres giriniz...");
        flag = false;
  /*  } else if (!ui->chkTermsOfService->checkState()) {
        QMessageBox::warning(this, "Kayıt", "Lütfen kayıt şartlarını kabul ediniz");
        flag = false;*/
    }

    return flag;
}

void frmKyt::Clear(){
    ui->txtName->clear();
    ui->txtSurname->clear();
    ui->txtUsername->clear();
    ui->txtPassword->clear();
    ui->txtPassword2->clear();
    ui->txtMail->clear();
    ui->txtPhoneNumber->clear();
    ui->txtAddress->clear();
}

void frmKyt::on_btnRegister_clicked()
{
    if(this->CheckInputs()){
        if(VTKontrolEt::instance()->IsOpen()){

   //////////////////////
            QSqlQuery q;

       QString ct = "CREATE TABLE if not exists user  ("
                         "id         integer prim key,"
                         "username   text ,"
                         "password   text ,"
                         "name       text ,"
                         "surname    text ,"
                         "phone      text ,"
                         "mail       text ,"
                         "address    text ,"
                         "dateRegister   text ,"
                         "dateLastLogin  TEXT ,"
                         "authorityLevel integer)" ;


            if (!q.exec( ct ))
            {
                qDebug() << "  'Kullanıcı kayıt' Dosyası Oluşturulamadı - "
                         << q.lastError() ;
            }
            else
                    qDebug() << "  'Kullanıcı Kayıt' Dosyası Oluşturuldu - ";


            /////////////////////////////



            QSqlQuery query;

            query.prepare(
               "INSERT INTO "
               "user ("
               "username, password, name, "
               "surname,  phone,    mail, "
               "address, dateRegister, dateLastLogin, "
               "authorityLevel) "
               "VALUES ("
               ":username, :password, :name, "
               ":surname,  :phone,    :mail, "
               ":address,  "
               ":dateRegister, :dateLastLogin,"
               ":authorityLevel)"
            );



            query.bindValue(":username", ui->txtUsername->text().trimmed());
            query.bindValue(":password", ui->txtPassword->text().trimmed());
            query.bindValue(":name", ui->txtName->text().trimmed());
            query.bindValue(":surname", ui->txtSurname->text().trimmed());
            query.bindValue(":phone", ui->txtPhoneNumber->text().trimmed());
            query.bindValue(":mail", ui->txtMail->text().trimmed());
            query.bindValue(":address", ui->txtAddress->toPlainText().trimmed());
            query.bindValue(":dateRegister", "");
            query.bindValue(":dateLastLogin", "");
            query.bindValue(":authorityLevel", 1);

            if(query.exec()){
                if(query.isActive()){
                    this->Clear();
                    QMessageBox::information(this, "Kayıt", "Kullanıcı başarı ile kayıt edildi...");
                    qDebug() << "Veritabanı Sorgusu Tamam ";
                    this->close();
                    return;
                }
            } else {
                QMessageBox::warning(this, "Kayıt", "Kullanıcı kayıt edilemedi !!!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Okul", "Veritabanı Bağlantısı Sağlanamdı !!!");
            qDebug() << "Veritabanı Bağlantısı Sağlanamdı !!!";
            return;
        }
    }
}
