#include "mw_main.h"
#include "globals.h"
#include "main.h"
#include <QTextCodec>

//#include <QZXing.h>

//using namespace zxing;
QString GLB_yetki = "İlk" ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    QImage imageToDecode("file.png");
    //QZXing decoder;
    //decoder.setDecoder( DecoderFormat_QR_CODE | DecoderFormat_EAN_13 );
    //QString result = decoder.decodeImage(imageToDecode);



    QTextCodec::codecForName("ISO-8859-9") ;

/*
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(142,45,197));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    qApp->setPalette(p);
*/
    // set style


 /*
    qApp->setStyle(QStyleFactory::create("Fusion"));
    // increase font size for better reading
    QFont defaultFont = QApplication::font();
    defaultFont.setPointSize(defaultFont.pointSize()+2);
    qApp->setFont(defaultFont);
    // modify palette to dark
    QPalette dp;
    dp.setColor(QPalette::Window,QColor(53,53,53));
    dp.setColor(QPalette::WindowText,Qt::white);
    dp.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
    dp.setColor(QPalette::Base,QColor(42,42,42));
    dp.setColor(QPalette::AlternateBase,QColor(66,66,66));
    dp.setColor(QPalette::ToolTipBase,Qt::white);
    dp.setColor(QPalette::ToolTipText,Qt::white);
    dp.setColor(QPalette::Text,Qt::white);
    dp.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
    dp.setColor(QPalette::Dark,QColor(35,35,35));
    dp.setColor(QPalette::Shadow,QColor(20,20,20));
    dp.setColor(QPalette::Button,QColor(53,53,53));
    dp.setColor(QPalette::ButtonText,Qt::white);
    dp.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
    dp.setColor(QPalette::BrightText,Qt::red);
    dp.setColor(QPalette::Link,QColor(42,130,218));
    dp.setColor(QPalette::Highlight,QColor(42,130,218));
    dp.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
    dp.setColor(QPalette::HighlightedText,Qt::white);
    dp.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));

    qApp->setPalette(dp);
*/

    a.setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
/// "#14dce7"
/// "#2effff"

   // darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::WindowText, QColor("#14dce7"));
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, QColor("#11f111"));
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, QColor("#66cc66"));
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);

    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");




    ///////////////////// splash screen
    //
    //*
    //    QPixmap pixmap(":/rsm/ex.png");
    //QSplashScreen splash(pixmap);
    ///splash.show();
    // wait for just 5 second and then show main window
    //a.thread()->sleep(1);
    //a.processEvents();//**////
    ///
    ///

  //  QSize size = qApp->screens()[0]->size();
    MW_main w ;
   // w->resize(size*.3);
    w.mwmain();
    qDebug ()<<"main";
    w.show ();
    //w.hide ();
    //splash.finish(w);
    return a.exec();
}

