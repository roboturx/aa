#include "logindialog.h"
#include "ui_logindialog.h"
#include "factory.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QFileDialog>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //    if(checkLicence())

    QString  IsEverythingOK {""};

    /// create db obj for use
    /// send driver type-path-name of db
    dBase = new DataBase;
    dBase->setDBDriver("QSQLITE");
    dBase->setDBPath("Records/");
    dBase->setDBName("database.db");
    dBase->DBconnect();

}

void LoginDialog::login()
{

    QString username = ui->username_edit->text();
    Factory *factory = new Factory(username,dBase );
    factory->show();
    factory->showMaximized();
    this->hide();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    QString username = ui->username_edit->text();
    QString password = ui->password_edit->text();

    QString tb_name{"tb_pr"};
    QString tb_personTableCreateStr {" CREATE TABLE IF NOT EXISTS tb_pr "
                                    "( f_prid INTEGER PRIMARY KEY, "
                                    "  f_prisim TEXT,      "
                                    "  f_prsoyad text,     "
                                    "  f_prusername text,  "
                                    "  f_prpassword text,  "
                                    "  f_pradres TEXT     )" };

    if (dBase->DBTableCreate(tb_name, tb_personTableCreateStr))
    {
        //    insertIntoHesapTable();
        QList<QString> ekle;
        // sql statement
        ekle << "INSERT INTO tb_pr ("
                "  f_prid      , "
                "  f_prisim    , "
                "  f_prsoyad   , "
                "  f_prusername, "
                "  f_prpassword, "
                "  f_pradres        )"

                "VALUES (:A, :B, :C, :D, :E, :F )";
        // field sayısı
        ekle << "6";
        // bind values
        ekle << "1"
             << "Murat"
             << "Balcı"
             << "a"
             << "a"
             << "Hızarhane Caddesi No:5 TOKAT";


        if (!dBase->addrecord(ekle))
            qDebug () << " İlk Kişi EKLENEMEDİ  " ;
        else
            qDebug () << " İlk Kişi EKLENDİ  " ;
    }


    QSqlQuery q;
    q.prepare("select * from tb_pr where f_prusername=? and f_prpassword=?");
    q.bindValue(0,username);
    q.bindValue(1,password);
    if(q.exec())
        if(q.next())
        {
            // login accepted
            int field = q.record().indexOf("f_prusername");
            ui->status->setText(q.value(field).toString()+" Girişi Onaylandı... ");
            login();
        }
        else
            ui->status->setText(username + " Kullanıcı kayıtlı DEĞİL !!");
    else{
        ui->status->setText("Not logged in");
        QSqlError err = q.lastError();
        QMessageBox::warning(this,"Error",err.text());
    }
}


bool LoginDialog::checkLicence()
{
    QString filepath = "C:/Windows/shaprianz.spz";
    QFile file(filepath);
    if(!file.exists()){
        QMessageBox::information(this,"Caution!",
                                 "<b>You are using this application "
                                 "without buying it.We can sue for "
                                 "5 lac rupees.Kindly contact the "
                                 "developer at <u>03316296093</u> to get "
                                 "your own software.");
        return false;
    }
    return true;
}



/*
void LoginDialog::setupConnection()
{
    //   db = QSqlDatabase::addDatabase("QSQLITE");
    //QString path = qApp->applicationDirPath()+"/Records/database.db";
    QString path = qApp->applicationDirPath()+"/Records/database.db";

qDebug() << "path : " << qApp->applicationDirPath();
qDebug() << "file : " << path;
qDebug() << "currentdir : " << QDir::currentPath() ;

QFile dbFile(path);
if(!dbFile.exists()){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Database","No database Exists."
                                                    "Do you want to open your own database?",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply==QMessageBox::Yes)
        path = QFileDialog::getOpenFileName(this,"Database",QDir::currentPath());
    else{
        qApp->closeAllWindows();
        qApp->exit(0);
    }
}
//  db.setDatabaseName(path);
qDebug() << path;
   if(db.open())
    { ui->status->setText("Database Connected");
        ////////////////////
        login();
        //////////////////////
    }
    else
        ui->status->setText("Database not connected");
}
*/
