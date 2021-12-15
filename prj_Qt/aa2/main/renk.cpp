#include "renk.h"
#include "globals.h"
Renk::Renk(QObject *parent) : QObject(parent)
{

    qDebug() << "Renk";
    //  QTextCodec::codecForName("ISO-8859-9") ;

    QString CeruleanBlue ("#98B4D4");  // fg
    QString Turquoise    ("#45B8AC");  // fg
    QString Serenity     ("#92A8D1");  // fg
    QString AspenGold    ("#FFD662");  // fg
    QString LivingCoral  ("#FF6F61");  // fg
    QString UltraViolet  ("#6B5B95"); // bg
    QString BrownGranite ("#615550"); // bg
    QString Eclipse      ("#343148"); // bg
    QString EveningBlue  ("#2A293E"); // bg
    QString NavyPeony    ("#223A5E"); // bg

    QString LushMeadow   ("#006E51");
    QString ChiliPepper  ("#9B2335");

    QPalette dP;
    dP.setColor(QPalette::Window       , QColor(EveningBlue));// window

    dP.setColor(QPalette::WindowText   , QColor(AspenGold));// label fg
    dP.setColor(QPalette::Base         , QColor(Eclipse));// text arkaplan 25,25,25));
    dP.setColor(QPalette::AlternateBase, QColor(ChiliPepper));//
    dP.setColor(QPalette::ToolTipBase  , QColor(LushMeadow));//
    dP.setColor(QPalette::ToolTipText  , QColor(LivingCoral));//

    dP.setColor(QPalette::PlaceholderText, QColor(NavyPeony));  //
    dP.setColor(QPalette::Text           , QColor(LivingCoral));//

    dP.setColor(QPalette::Button         , QColor(Eclipse)); //
//    dP.setColor(QPalette::Mid, QColor(EveningBlue));
    dP.setColor(QPalette::ButtonText     , QColor(Turquoise)); //
    dP.setColor(QPalette::BrightText     , QColor(Serenity) );           //

    dP.setColor(QPalette::Link, QColor(LushMeadow));
    dP.setColor(QPalette::LinkVisited , QColor(LushMeadow));

    dP.setColor(QPalette::Highlight, QColor(NavyPeony));
    dP.setColor(QPalette::HighlightedText, QColor(CeruleanBlue) );

 qDebug() << "Renk Winnnnnnnnnnn";
#ifdef LINUX
    qApp->setPalette(dP)
    qDebug() << "Renk Lınux";
#endif
qApp->setPalette(dP);

   // qApp->setStyleSheet("QToolTip { color: #ffffff;
    //background-color: #2a82da; border: 1px solid white; }");



}
