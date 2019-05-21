
#include "frmGrs.h"
#include "ui_frmGrs.h"
#include "frmKyt.h"
#include "frmAna.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QLabel>
#include "VTKontrol.h"
#include <QApplication>
#include <QSqlError>
#include <QDebug>
#include <QCloseEvent>

frmGrs::frmGrs(QWidget *parent) : QDialog(parent),
    ui(new Ui::frmGrs)
{
    qApp->setQuitOnLastWindowClosed(false);

    ui->setupUi(this);
    window()->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window()->size(), qApp->desktop()->availableGeometry()));

    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    this->setWindowTitle("Yetkili Giriş Kontrolü");
    if(VTKontrolEt::instance()->IsOpen()){
        ui->lblStatus->setText("Veritabanı Bağlantısı Sağlandı...");
        QTextStream(stdout) << "Bağlantı Tamam";
    } else {
        ui->lblStatus->setText("Veritabanı Bağlantısı Sağlanamadı!!!");
        QTextStream(stdout) << "Bağlantı Hatası !!!";
    }
}

frmGrs::~frmGrs()
{
    this->setFixedSize(this->width(),this->height());
    delete ui;
}

void frmGrs::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton mboxSelect = QMessageBox::question( this, "Okul Takip Yazılımı", "Çıkmak istediğinizden emin misiniz?", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (mboxSelect != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        QApplication::quit();
    }
}

void frmGrs::on_btnRegister_clicked()
{
    frmKyt *r = new frmKyt(this);
    r->setModal(true);
    r->show();
}

void frmGrs::on_btnLogin_clicked()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text().trimmed();


    if (username.isEmpty()) {
        ui->lblStatus->setText("Kullanıcı adı girmelisiniz...");
        return;
    } else if (password.isEmpty()) {
        ui->lblStatus->setText("Şifre girmelisiniz...");
        return;
    }

    QSqlQuery query;

    query.prepare(
       "SELECT * FROM "
       "user "
       "WHERE "
       "username = :username AND password = :password"
    );

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if(query.exec()){
        if(query.isActive()){
            int count = 0;

            while(query.next()){
                count++;
            }

            if(count == 1){
                ui->lblStatus->setText("Yetkili Giriş Sağlandı...");
                this->hide();
                this->LoginOK(username);
                return;
            } else if (count > 1){
                ui->lblStatus->setText("Aynı isimde birden fazla Kullanıcı adı ve Şifre var !!!");
            } else if (count < 1){
                ui->lblStatus->setText("Hatalı Giriş Denemesi ");
            }
        } else {
            ui->lblStatus->setText("Sorgu Aktivite Hatası !!!");
            qDebug() << query.lastError();
        }
    } else {
        ui->lblStatus->setText("Veritabanı Hatası !!!");
        qDebug() << query.lastError();
    }
}

