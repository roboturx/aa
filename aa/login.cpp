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
    QTimer::singleShot(0, lE_user, SLOT(setFocus()));

    QGridLayout *lg2 = new QGridLayout(this);
    lg2->addWidget(lB_user,0,0,1,1);
    lg2->addWidget(lE_user,0,1,1,2);
    lg2->addWidget(lB_pass,0,3,1,1);
    lg2->addWidget(lE_pass,0,4,1,2);

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

    keyESC = new QShortcut(this);   // Initialize the object
    keyESC->setKey(Qt::Key_Escape);    // Set the key code
    // connect handler to keypress
    connect(keyESC, &QShortcut::activated , this,
            &Login::logout );

    /*QShortcut * sl_ESC = new QShortcut(
                QKeySequence(Qt::Key_Escape,
                    Qt::Key_Escape), this ,
                 SLOT( logex()  ));
*/
    //Login::logexited ()
    //sl_ESC->setAutoRepeat(false);

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

    logex("ESC");
}


Login::~Login()
{

}

/*
void Login::quitApp(QString nereden)
{
qDebug()<<"quitapp başı";
    qDebug() << "quitting from "<<nereden;
    try
    {
        if(VTKontrolEt::instance()->IsOpen())
        {
            VTKontrolEt::instance()->Disconnect();
            //statusbar->showMessage("Veritabanı bağlantısı KAPATILDI ...", 1000);
            qDebug() << "DISConnected from quitApp...";
            QCoreApplication::exit(0);
        }

     //   fade(false);
    }
    catch (...)
    {
        qDebug() << "Hata 001 - Code::mw_main catched";
        QCoreApplication::exit(1);

    }
qDebug()<<"logexited başı";
    logexited(" ** quitapp ");
}

*/


void Login::logex(QString nereden)
{
    try
    {
        if(VTKontrolEt::instance()->IsOpen())
        {
            VTKontrolEt::instance()->Disconnect();
            if( ! VTKontrolEt::instance()->IsOpen())
            {
                qDebug() << "Disconnected from " << nereden;
                QApplication::setQuitOnLastWindowClosed(true);


                this->destroy (true,true);

                 qDebug() << "Destroyed";
                this->close ();
                  qDebug() << "Closed";
                qApp->quit ();
                 qDebug() << "Quited";
                 QApplication::exit(0);
                 qDebug() << "Exited";
                 qDebug() << "All windows Closing";

                 QApplication::closeAllWindows();

                 qDebug() << "All windows Closed";
            }
        }

        //fade(false);

    }
    catch (...)
    {
        qDebug() << "Hata wd_logg" << nereden;
        QApplication::exit(1);
    }

}

void Login::logined()
{

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
