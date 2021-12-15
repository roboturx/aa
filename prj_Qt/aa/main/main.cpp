#include "mw_main.h"
#include "globals.h"

QString GLB_yetki = "İlk" ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::codecForName("ISO-8859-9") ;

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


#ifdef LINUX
    qApp->setPalette(dP);
#endif


   // qApp->setStyleSheet("QToolTip { color: #ffffff;
    //background-color: #2a82da; border: 1px solid white; }");




    ///////////////////// splash screen
    //
    //
    //    QPixmap pixmap(":/rsm/ex.png");
    //    QSplashScreen splash(pixmap);
    //    splash.show();
    //    // wait for just 5 second and then show main window
    //    a.thread()->sleep(0);
    //    a.processEvents();
    ///

    QSize size = qApp->screens()[0]->size();
    MW_main w ;

    //w.resize(size*.6);
    w.resize(size);
    qDebug ()<<"main";
    w.show ();
    w.login ();


    //w.hide ();
    //splash.finish(w);
    return QApplication::exec();
}

//    a.setStyle(QStyleFactory::create("Fusion"));
/// "#14dce7"
/// "#2effff"   #11f111
///
///

// 2019 - Living Coral    HEX: #FF6F61  PANTONE 16-1546
// 2018 - Ultra Violet   HEX: #6B5B95  PANTONE 18-3838

// The Hottest Autumn 2019 / Winter 2020 Colors:
// Chili Pepper   HEX: #9B1B30  PANTONE 19-1557
// Biking Red     HEX: #77212E  PANTONE 19-1650
// Crème de Pêche HEX: #F5D6C6  PANTONE 12-1110
// Peach Pink     HEX: #FA9A85  PANTONE 15-1530
// Rocky Road     HEX: #5A3E36  PANTONE 19-1234
// Fruit Dove     HEX: #CE5B78  PANTONE 17-1926
// Sugar Almond   HEX: #935529  PANTONE 18-1155
// Dark Cheddar   HEX: #E08119  PANTONE 15-1150
// Galaxy Blue    HEX: #2A4B7C  PANTONE 19-4055
// BluestoneH     HEX: #577284  PANTONE 18-4217
// Orange Tiger   HEX: #F96714  PANTONE 16-1358
// Eden           HEX: #264E36  PANTONE 19-6050

// The Autumn 2019 / Winter 2020 Classics:

// Vanilla Custard HEX: #F3E0BE PANTONE 19-12-0815
// Evening Blue    HEX: #2A293E PANTONE 19-3815

// Paloma          HEX: #9F9C99 PANTONE 16-0000
// Guacamole       HEX: #797B3A PANTONE 17-0530

// The Hottest Spring / Summer Colors 2019

// Fiesta         HEX: #DD4132 PANTONE 17-1564
// Jester Red     HEX: #9E1030 PANTONE 19-1862
// Turmeric       HEX: #FE840E PANTONE 15-1264
// Living Coral   HEX: #FF6F61 PANTONE 16-1546
// Pink Peacock   HEX: #C62168 PANTONE 18-2045
// Pepper Stem    HEX: #8D9440 PANTONE 17-0542
// Aspen Gold     HEX: #FFD662 PANTONE 13-0850
// Princess Blue  HEX: #00539C PANTONE 19-4150
// Toffee         HEX: #755139 PANTONE 18-1031
// Mango Mojito   HEX: #D69C2F PANTONE 15-0960
// Terrarium Moss HEX: #616247 PANTONE 18-0416
// Sweet Lilac    HEX: #E8B5CE PANTONE 14-2808
// Soybean        HEX: #D2C29D PANTONE 13-0919
// Eclipse        HEX: #343148 PANTONE 19-3810
// Sweet Corn     HEX: #F0EAD6 PANTONE 11-0106
// Brown Granite  HEX: #615550 PANTONE 19-0805

/*

Ultra Violet HEX: #6B5B95 PANTONE 18-3838   Color of the Year 2018

Red Pear      HEX: #7F4145 Pantone 19-1536 The Hottest Fall / Winter Colors 2018
Valiant Poppy HEX: #BD3D3A Pantone 18-1549
Nebulas Blue  HEX: #3F69AA Pantone 18-4048
Ceylon Yellow HEX: #D5AE41 Pantone 15-0850
Martini Olive HEX: #766F57 Pantone 18-0625
Russet Orange HEX: #E47A2E Pantone 16-1255
Crocus Petal  HEX: #BE9EC9 Pantone 15-3520
Limelight     HEX: #F1EA7F Pantone 12-0740
Quetzal Green HEX: #006E6D Pantone 18-5025

The Classic Fall / Winter Colors 2018

Sargasso Sea HEX: #485167 Pantone 19-4031
Tofu HEX: #EAE6DA Pantone 11-4801
Almond Buff HEX: #D1B894 Pantone 14-1116
Quiet Gray HEX: #BCBCBE Pantone 14-4107
Meerkat HEX: #A9754F Pantone 16-1438

The Hottest Spring Colors 2018
Meadowlark HEX: #ECDB54 Pantone 13-0646
Cherry Tomato HEX: #E94B3C Pantone 17-1563
Little Boy Blue HEX: #6F9FD8 Pantone 16-4132
Chili Oil HEX: #944743 Pantone 18-1440
Pink Lavender HEX: #DBB1CD Pantone 14-3207
Blooming Dahlia HEX: #EC9787 PANTONE 15-1520
Arcadia HEX: #00A591 PANTONE 16-5533
Ultra Violet HEX: #6B5B95 PANTONE 18-3838
Emperador HEX: #6C4F3D Pantone 18-1028
Almost Mauve HEX: #EADEDB Pantone 12-2103
Spring Crocus HEX: #BC70A4 PANTONE 17-3020
Lime Punch HEX: #BFD641 PANTONE 13-0550

Spring 2018 Classic Color Palette
Sailor Blue HEX: #2E4A62 PANTONE 19-4034
Harbor Mist HEX: #B4B7BA PANTONE 14-4202
Warm Sand HEX: #C0AB8E PANTONE 15-1214
Coconut Milk HEX: #F0EDE5 PANTONE 11-0608

Color of the Year 2017
Greenery HEX: #92B558 Pantone 15-0343

The Hottest Fall Colors for 2017

Grenadine HEX: #DC4C46 Pantone 17-1558
Tawny Port HEX: #672E3B Pantone 19-1725
Ballet Slipper HEX: #F3D6E4 Pantone 13-2808
Butterum HEX: #C48F65 Pantone 16-1341
Navy Peony HEX: #223A5E Pantone 19-4029
Neutral Gray HEX: #898E8C Pantone 17-4402
Shaded Spruce HEX: #005960 Pantone 19-4524
Golden Lime HEX: #9C9A40 Pantone 16-0543
Marina HEX: #4F84C4 Pantone 17-4041
Autumn Maple HEX: #D2691E Pantone 17-1145

The 10 Hottest Spring Colors for 2017
Pantone told us that in the Spring of 2017 we would wear bright and vivid colors  as well as those that convey a sense of earthiness:

Niagara HEX: #578CA9 Pantone 17-4123
Primrose Yellow HEX: #F6D155 Pantone 13-0755
Lapis Blue HEX: #004B8D Pantone 19-4045
Flame HEX: #F2552C Pantone 17-1462
Island Paradise HEX: #95DEE3 Pantone 14-4620
Pale Dogwood HEX: #EDCDC2 Pantone 13-1404

Pink Yarrow HEX: #CE3175 Pantone 17-2034
Kale HEX: #5A7247 Pantone 18-0107
Hazelnut HEX: #CFB095 Pantone 14-1315

The 10 Hottest Fall Colors for 2016
Pantone  told us that in the Fall 2016 we would wear colors that suggests strength, confidence, and complexity.
The hues also reflect our desire for tranquility and optimism.

Riverside HEX: #4C6A92 Pantone 17-4028
Airy Blue HEX: #92B6D5 Pantone 14-4122
Sharkskin HEX: #838487 Pantone 17-3914
Aurora Red HEX: #B93A32 Pantone 18-1550
Warm Taupe HEX: #AF9483 Pantone 16-1318
Dusty Cedar HEX: #AD5D5D Pantone 18-1630
Lush Meadow HEX: #006E51 Pantone 18-5845
Spicy Mustard HEX: #D8AE47 Pantone 14-0952

Potter's Clay HEX: #9E4624 Pantone 18-1340
Bodacious HEX: #B76BA3 Pantone 17-3240

The 10 Hottest Spring Colors for 2016
The Pantone fashion color report for the Spring 2016 told us that we would wear colors that suggests health, peace, and accessibility because they make us feel comfortable.
The 2016 spring hues also reflect our access to modern art and a desire for natural surroundings.

Rose Quartz HEX: #F7CAC9

Designers 2016: TOSIA, Houghton, M.PATMOS, Charles Youssef
Goes with: Peach Echo, Serenity, Lilac Grey

Peach Echo HEX: #F7786B

Designers 2016: Christan Siriano, Rebecca Minkhoff, Dennis Basso, Ella Moss
Goes with: Rose Quartz, Serenity, Lilac Grey

Serenity HEX: #91A8D0

Designers 2016: Emilio Sosa, Rachel Pally Harbison

Goes with: Buttercup, Snorkel Blue, Peach Echo

Snorkel Blue HEX: #034F84

Designers 2016 Georgine, Tasashi Shoji, WHIT NY, Angelys Balek
Goes with: Buttercup, Iced Coffee, Peach Echo

Limpet Shell HEX: #98DDDE

Designers 2016 Ground Zero, O'2nd, Kung Katherine
Goes with: Iced Coffee, Peach Echo, Rose Quartz

Lilac Grey HEX: #9896A4

Designers 2016: KARIGRAM, Rebecca Vallance, Yoana Baraschi
Goes with: Fiesta, Green Flash, Iced Cofee

Iced Coffee HEX: #B18F6A

Designers 2016: Noon by Noor, Daniel Silverstain
Goes with: Rose Quartz, Serenity, Lilac Grey

Fiesta HEX: #DD4132

Designers 2016: Pamella Roland, Malone Souliers
Goes with: Snorkel Blue, Green Flash, Limpet Shell

Buttercup HEX: #FAE03C

Designers 2016: Charles Á Ron,David Hart
Goes with: Snorkel Blue, Serenity, Lilac Grey

Green Flash HEX: #79C753

Designers 2015 Angel Sanchez, Nicole Miller
Goes with: Snorkel Blue, Serenity, Limpet Shell

Colors of the Year 2000-2019

2019 Living Coral HEX: #FF6F61 RGB(255, 111, 97) PANTONE 16-1546
2018 Ultra Violet HEX: #6B5B95 RGB(107, 91, 149) PANTONE 18-3838
2017 Greenery Hex #88B04B RGB(136, 176, 75) Pantone 15-0343
2016 Rose Quartz Hex #F7CAC9 RGB(247, 202, 201) Pantone 13-1520
2016 Serenity Hex #92A8D1 RGB(146, 168, 209) Pantone 15-3919
2015 Marsala Hex #955251 RGB(149, 82, 81) Pantone 18-1438
2014 Radiand Orchid Hex #B565A7 RGB(181, 101, 167) Pantone 18-3224
2013 Emerald Hex #009B77 RGB(0, 155, 119) Pantone 17-5641
2012 Tangerine Tango Hex #DD4124 RGB(221, 65, 36) Pantone 17-1463
2011 Honeysucle Hex #D65076 RGB(214, 80, 118) Pantone 18-2120
2010 Turquoise Hex #45B8AC RGB(68, 184, 172) Pantone 15-5510
2009 Mimosa Hex #EFC050 RGB(239, 192, 80) Pantone 14-0848
2008 Blue Izis Hex #5B5EA6 RGB(91, 94, 166) Pantone 18-3943
2007 Chili Pepper Hex #9B2335 RGB(155, 35, 53) Pantone 19-1557
2006 Sand Dollar Hex #DFCFBE RGB(223, 207, 190) Pantone 13-1106
2005 Blue Turquoise Hex #55B4B0 RGB(85, 180, 176) Pantone 15-5217
2004 Tigerlily Hex #E15D44 RGB(225, 93, 68) Pantone 17-1456
2003 Aqua Sky Hex #7FCDCD RGB(127, 205, 205) Pantone 14-4811
2002 True Red Hex #BC243C RGB(188, 36, 60) Pantone 19-1664
2001 Fuchsia Rose Hex #C3447A RGB(195, 68, 122) Pantone 17-2031
2000 Cerulean Blue Hex #98B4D4 RGB(152, 180, 212) Pantone 15-4020
*/



/*
QPalette::Light     2     Lighter than Button color.
QPalette::Midlight  3     Between Button and Light.
QPalette::Dark      4     Darker than Button.
QPalette::Mid       5     Between Button and Dark.
QPalette::Shadow    11    A very dark color. By default, the shadow color is Qt::black.

 */


//    QPalette dP;
//    dP.setColor(QPalette::Window,
//                QColor(EveningBlue));

//    dP.setColor(QPalette::WindowText,
//                QColor(AspenGold)); // label fg
//    dP.setColor(QPalette::Base,
//                QColor(LushMeadow)); // text arkaplan 25,25,25));
//    dP.setColor(QPalette::AlternateBase,
//                QColor(ChiliPepper));//53,53,53));
//    dP.setColor(QPalette::ToolTipBase,
//                QColor(ChiliPepper));
//    dP.setColor(QPalette::ToolTipText,
//                QColor(CeruleanBlue));

//    dP.setColor(QPalette::PlaceholderText,
//                QColor(LushMeadow));
//    dP.setColor(QPalette::Text, QColor(LivingCoral));

//    dP.setColor(QPalette::Button, QColor(EveningBlue));
////    dP.setColor(QPalette::Mid, QColor(EveningBlue));
//    dP.setColor(QPalette::ButtonText, QColor(LivingCoral));
//    dP.setColor(QPalette::BrightText, Qt::red);

//    dP.setColor(QPalette::Link, QColor(42, 130, 218));
//    dP.setColor(QPalette::LinkVisited , QColor(42, 130, 218));

//    dP.setColor(QPalette::Highlight, QColor(UltraViolet));
//    dP.setColor(QPalette::HighlightedText, QColor(LivingCoral) );

//    qApp->setPalette(dP);
//   // qApp->setStyleSheet("QToolTip { color: #ffffff;
//    //background-color: #2a82da; border: 1px solid white; }");

