#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)

{
    /// login widget
    /////////////////////////////////////
    qDebug() << "Login";

    QLabel *lB_user = new QLabel("Kullanıcı ");
    QLabel *lB_pass = new QLabel("Şifre ");
    lE_user = new QLineEdit ;
    lE_pass = new QLineEdit ;

    /// kullanıcı girişine fokusla
    QTimer::singleShot(0, lE_user, SLOT(setFocus()));

    /// formu hazırla
    auto *gL_loginlayout = new QGridLayout(this);
    gL_loginlayout->addWidget(lB_user,0,0,1,1);
    gL_loginlayout->addWidget(lE_user,0,1,1,2);
    gL_loginlayout->addWidget(lB_pass,0,3,1,1);
    gL_loginlayout->addWidget(lE_pass,0,4,1,2);

    this->setMaximumHeight (50);
    this->setMaximumWidth (400);
    this->setMinimumWidth (400);
    //    this->setAllowedAreas (Qt::NoToolBarArea  );
    this->setWindowFlags(Qt::Window |
                         Qt::FramelessWindowHint |
                         Qt::WindowStaysOnTopHint );
    //    this->setModal (true);
    this->show();
    this->move(410,310);

    /// tusları kontrol et
    keyESC = new QShortcut(this);   // Initialize the object
    keyESC->setKey(Qt::Key_Escape);    // Set the key code
    // connect handler to keypress

    /// esc basılırsa çıkışa yönlendir
    connect(keyESC, &QShortcut::activated , this,
            &Login::logout );


    /// enter veya return a basılırsa girişe yönlendir
    QShortcut * sl_ENTER = new QShortcut(
                QKeySequence(Qt::Key_Enter), this,
                SLOT(logined() ));
    sl_ENTER->setAutoRepeat(false);

    QShortcut * sl_RETURN = new QShortcut(
                QKeySequence(Qt::Key_Return),this,
                SLOT(logined() ));
    sl_RETURN->setAutoRepeat(false);

}


void Login::logout()
{
    // esc basılmış - çıkış işlemlerine git
    logex("ESC");
}


Login::~Login()
= default;

void Login::logex(const QString& nereden)
{
    // esc basılmış - çıkış işlemlerini oluştur ve programı sonlandır
    try
    {
        if(VTKontrolEt::instance()->IsOpen())
        {
            VTKontrolEt::instance()->Disconnect();
            if( ! VTKontrolEt::instance()->IsOpen())
            {
                qDebug() << "Disconnected from " << nereden;
                QApplication::setQuitOnLastWindowClosed(true);
                QApplication::closeAllWindows();

                qDebug() << "All windows Closed";
                this->destroy (true,true);

                 qDebug() << "Destroyed";
                this->close ();
                  qDebug() << "Closed";
                qApp->quit ();
                 qDebug() << "Quited";
                 QApplication::exit(0);
                 qDebug() << "Exited";
                 qDebug() << "All windows Closing";


            }
        }

        //fade(false);

    }
    catch (...)
    {
        // çıkışta hata !!!!
        qDebug() << "Hata wd_logg" << nereden;
        QApplication::exit(1);
    }

}

void Login::logined()
{
    /// enter a basılmış - veritabanı kullanıcı kontrolunu yap

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
            //        yaz("- ? - ","Yanlış kullanıcı adı veya Şifre");
            qDebug()<<"wrong pass or user";
        }
        else if (ccc > 1)
        {
            //      yaz("- ? - ","İki ayrı çalışan'da aynı tanımlama");
            qDebug()<<"double user";
        }

        else if (ccc == 1)
        {
            qry.prepare("SELECT yetki FROM dbtb_clsn "
                        "WHERE (username='"+username+"' "
                                                     "AND password='"+password+"')");
            qry.exec();
            if (qry.first())
            {
                GLB_yetki = qry.value("yetki").toString() ;
                //              this->setWindowFlags(Qt::Window );

                //              MW_main::setAcceptDrops (true);

                //                toolBar->setVisible (false);


                //      qDebug()<<"pass okkkk";
                //    qDebug()<<qry.record().value (0).toString ();
                emit logok(qry.record().value (0).toString (), username);

                this->hide ();
            }
            //    yaz("--- ","Tam yetkiyle giriş sağlandı...");

        }
    }
}
