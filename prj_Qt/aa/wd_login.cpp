#include "wd_login.h"
#include "globals.h"
#include "mw_main.h"

using namespace std;

WD_login::WD_login() : QWidget()
{
  //  QLabel *x = new QLabel("Murat BALCI +905053202240");
  //  x->setFont (QFont ("code128",10));
    QLabel *lB_user = new QLabel;
    lB_user->setText("Kullanıcı Adı");
    QLabel *lB_pass = new QLabel("Şifre");

    QLCDNumber *lcd = new QLCDNumber(12,this);
    lcd->display (12);


    lE_user = new QLineEdit() ;
    lE_pass = new QLineEdit() ;


    QPushButton *pb_ok   = new QPushButton("Giriş");

    pb_ok->setIcon (style()->standardIcon(QStyle::SP_DialogOkButton ) );
    pb_ok->setStyleSheet ("QPushButton:hover { "
                          "color: yellow   ; "
                          "background-color: green ;"
                          "font : bold     ;"
                          " }"
                          );




    QPushButton *pb_out  = new QPushButton ("Çıkış");
    pb_out->setStyleSheet ("QPushButton:hover { color: yellow ; "
                           "background-color: green ;"
                           "font : bold  }");


    pb_ok->setDefault(true);



    gr = new QGroupBox();
    durum = new QTextEdit;
   // QDate dt;

    //   this->setGeometry(100,100,300,200);
    //durum->append(dt.toString);
    durum->append (("\nLütfen,"
                   "\n  Kullanıcı Adı ve Şifre  "
                   "\n               Giriniz..."));
 //    QWidget *xx= new QWidget();
    QGridLayout *lg = new QGridLayout(this);
    lg->addWidget(lB_user,0,0,1,1);
    lg->addWidget(lE_user,0,1,1,2);
    lg->addWidget(lB_pass,1,0,1,1);
    lg->addWidget(lE_pass,1,1,1,2);
    lg->addWidget(pb_out ,2,0,1,1);
    lg->addWidget(pb_ok  ,2,1,1,2);
   // lg->addWidget(durum  ,3,0,1,3);
   // lg->addWidget(lcd    ,5,2,1,1);
   // lg->addWidget(x      ,5,0,1,2);




    //this->showFullScreen();
    //xx->setWindowOpacity(100);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_NoSystemBackground);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setWindowTitle("Kullanıcı Giriş Kontrolu");

    //this->setStyleSheet("background-color: rgba(0,0,0,10);"
                    //"color:rgba(220,220,220,220)");
//xx->show();
    //statusBar()->showMessage(tr("Readyxxxxxxx"));
    connect(pb_ok, &QPushButton::clicked,
            this,&WD_login::on_pb_ok_clicked);
    connect(pb_out,&QPushButton::clicked,
            this,&WD_login::on_pb_out_clicked);
    QShortcut * shortcut = new QShortcut(
                QKeySequence(Qt::Key_Escape),this,
                SLOT(on_pb_out_clicked() ));
    shortcut->setAutoRepeat(false);
}


void WD_login::on_pb_ok_clicked()
{
    /// Çalışan dosyasını kontrol et
    VTDosyaKontrol();

    QString username =  lE_user->text();  //"a"; //
    QString password =  lE_pass->text();  //"a"; //
    QSqlQuery qry;

    qry.prepare("SELECT * FROM dbtb_clsn "
                "WHERE (username='"+username+"' "
                   "AND password='"+password+"')");
    if( qry.exec() )
    {
        int ccc;
        ccc = 0 ;
        while (qry.next())     {
            ccc++;
        }
        if (ccc < 1)
        {
            durum->append(QString::fromLocal8Bit ("Yanlış kullanıcı adı veya Şifre"));
        }
        else if (ccc > 1)
        {
            durum->append(QString::fromLocal8Bit ("İki ayrı çalışan'da aynı tanımlama"));
        }

        else if (ccc == 1)
        {
//            qry.prepare("SELECT yetki FROM dbtb_clsn "
//                        "WHERE (username='"+username+"' "
//                                                     "AND password='"+password+"')");
//            qry.exec();
            if (qry.first())
            {
                GLB_yetki = qry.value("yetki").toString() ;

            }


            durum->setText (QString::fromLocal8Bit ("Tam yetkiyle giriş sağlandı..."));
            durum->append (QString::fromLocal8Bit ("Veri Dosyaları kontrol ediliyor..."));
            durum->append (QString::fromLocal8Bit ("Lütfen Bekleyiniz..."));

            unlock_prg();
        }
    }
}





void WD_login::unlock_prg()
{
    emit unlocked();
}

WD_login::~WD_login()
{
    delete lE_user;
    delete lE_pass;
    delete gr;
    delete durum;

    qDebug() << "Login ~ ";
}

void WD_login::reject()
{
    emit quitApp();
    qDebug() << "Login rejected";
}
void WD_login::showEvent(QShowEvent *)
{

    // qDebug ()  <<" 'showEvent ' - Login ";
    // ui->durum->append("window activated");
    // qApp->blockSignals(true);
    // ui->durum->append("signals true");

    //ui->groupBoxLogin->show();
}

void WD_login::on_pb_out_clicked()
{
   emit quitApp();
}

void WD_login::VTDosyaKontrol()
{
    QSqlQuery   q;
    QString     ct;
    QStringList inserts;


    //// Veritabanında dosya varmý yoksa oluþtur ve ilk kaydÄ± ekle
    if(VTKontrolEt::instance()->Connect())
    {
        if ( ! VTKontrolEt::instance()->
             GetDB().tables().contains( "dbtb_clsn"))
        {
            /// calişan create
            ///

            ct = "CREATE TABLE IF NOT EXISTS dbtb_clsn"
                 "("
                 "  kod_pr	    INTEGER PRIMARY KEY  , "
                 "  isim		TEXT ,"
                 "  soyad	    TEXT ,"
                 "  tckimlik    TEXT ,"
                 "  dogumyeri   TEXT ,"
                 "  dogumtarihi DATE ,"
                 "  babaadi     TEXT ,"
                 "  bolum	    TEXT ,"
                 "  meslek      int ,"
                 "  gorev	    TEXT ,"
                 "  adres		TEXT ,"
                 "  sehir       TEXT ,"
                 "  tel_cep	    TEXT ,"
                 "  tel_ev	    TEXT ,"
                 "  eposta      TEXT ,"
                 "  username	TEXT ,"
                 "  password	TEXT ,"
                 "  yetki		TEXT ,"
                 "  resim       BLOB  )" ;

            if (!q.exec( ct ))
            {
                qDebug() << "Çalışan DosyasÄ± Oluşturulamadı - "
                         << q.lastError() ;
            }
            else
            {
                qDebug() << "Çalışan Dosyası YENİ Oluşturuldu - ";
            }
        }

        q.prepare("SELECT * FROM dbtb_clsn ");
        if( q.exec() )
        {
            int ccc;
            ccc = 0 ;
            while (q.next())
            {
                ccc++;
            }
            if (ccc < 1)
            {
                inserts << "INSERT INTO dbtb_clsn "
                           "( "
                           "isim, soyad, "
                           "bolum, meslek, gorev, "
                           "adres, sehir, "
                           "tel_cep, tel_ev, eposta,"
                           " username, password, yetki"
                           ") "
                           "VALUES "
                           "("
                           "'Murat', 'BALCI', "
                           "'bilgi işlem', 'CASE', 'Developer', "
                           "'adres', 'sehir', "
                           "'505 320 22 40', '356 232 91 01', 'roboturx@gmail.com', "
                           "'a','a', 'a'"
                           " )" ;

                foreach (QString qry , inserts)
                {
                    if ( !q.exec(qry) )
                        qDebug()  << " HATA - İlk ÇALIŞAN Eklenemedi - "
                                  << q.lastError() ;
                    else
                        qDebug()  << " İlk ÇALIŞAN Eklendi - ";

                }
            }

            /// meslekler dosyasý
            ///
            ///
            if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mslk"))
            {
                QSqlQuery query;
                if (! query.exec("create table if not exists "
                                 "dbtb_mslk (id int, meslek TEXT)"))
                {
                    qDebug() << "MESLEK DosyasÄ± Oluşturulamadı - "
                             << q.lastError() ;
                }
                else
                {
                    qDebug() << "MESLEK Çalışan Dosyası YENİ Oluşturuldu - ";
                    query.exec("insert into dbtb_mslk values(101, 'Makina Mühendisi')");
                    query.exec("insert into dbtb_mslk values(102, 'Operatör-Loader')");
                    query.exec("insert into dbtb_mslk values(103, 'Operator-Backhoe')");
                }
            }
        }
    }
    else
    {
        qDebug() << "NO Connection for Login" ;
    }
}


void WD_login::quitApp()
{

    try
    {
        if(VTKontrolEt::instance()->IsOpen())
        {
            VTKontrolEt::instance()->Disconnect();
            //statusbar->showMessage("Veritabanı bağlantısı KAPATILDI ...", 1000);
            qDebug() << "Disconnected ...";
        }

        //fade(false);

  QApplication::exit(0);

    }
    catch (...)
    {
        qDebug() << "Hata";
        QApplication::exit(1);
    }

}

