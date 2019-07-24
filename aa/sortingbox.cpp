#include <QtWidgets>
#include <QObject>
#include <stdlib.h>
#include "sortingbox.h"
#include "mw_main.h"



int SortingBox::count=1;
int SortingBox::col=20;
int SortingBox::row=65;


SortingBox::SortingBox(QWidget* parent)
{

    isEmri = new hC_IE;
    isEmri->tbsetup ();
    isEmri->hide ();

    setMouseTracking(true);
    setBackgroundRole(QPalette::Base);
    itemInMotion = nullptr;
    squarePath.addRect(QRect(0, 0, 160, 100));
    QToolButton* Bt1 = createToolButton(tr("İŞ EMRİ"),
                                       QIcon(":/rsm/ex.ico"),
                                       SLOT(listele()),
                                       "İş Emri");

    QToolButton* Bt2 = createToolButton(tr("İŞ EMRİ EKLE"),
                                            QIcon(":/rsm/ex.ico"),
                                            SLOT(createIsEmri()),
                                            "İş Emri");
    Bt1->setGeometry(2,2,96,30);
    Bt2->setGeometry(100,2,96,30);


    auto boxWidget = new QWidget(this);
    auto boxGrid = new QGridLayout(boxWidget);
    boxGrid->addWidget (Bt1,0,0,1,1);
    boxGrid->addWidget (Bt2,0,1,1,1);


    /// bu fonksiyonun içinden kontrol edelim


}

void SortingBox::listele()
{
    ///// toolbutton için
    ////////////////// iş emirlerini ekrana listele
    shapeItems.clear ();
    SortingBox::count = 0 ;
    SortingBox::row = 65 ;
    SortingBox::col = 20 ;
    QSqlQuery query("SELECT * FROM ie_dbtb WHERE ie_durum != 'Tamamlandı'");
    if (query.isActive ())
    {
        qDebug()<< "active " ;
    }
    else {
        qDebug()<< "not active "<< query.lastError ().text ();
    }

    while (query.next())
    {
        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData( query.value (9).toByteArray () );
        setPixmap (outPixmap);
        setCurrentRecord (query.record());
        createNewSquare ();
    }

}


//int SortingBox::count(int i)
//{
//    static int count = 1;
//    qDebug() <<"count *****************************  "<< count;
//    // count
//    if ( i == 0 )
//    {
//        // count u sıfırla
//        qDebug() <<"count 0  "<< count;
//        count = 1 ;
//        qDebug() <<"count 0  "<< count<<endl;
//    }
//    else if ( i == 1 )
//    {
//        qDebug() <<"count 1  "<< count;
//        // count u çoğalt
//        count++;
//        qDebug() <<"count 1  "<< count<<endl;
//    }
//    return count;
//}


void SortingBox::createNewSquare( )
{
    createShapeItem(squarePath,
                    tr("Excavator <%1>").arg( count++ ),
                    randomItemPosition(),
                    randomItemColor(),
                    getCurrentRecord() ,
                    getPixmap() );
}

void SortingBox::createIsEmri()
{
    //isEmri->tb_view->pB_ekle->clicked ();
    isEmri->show ();

    QSqlRecord newRecord;



    createNewSquare( );
}



void SortingBox::createShapeItem(const QPainterPath &path,
                                 const QString &toolTip,
                                 const QPoint &pos,
                                 const QColor &color,
                                 const QSqlRecord &record,
                                 const QPixmap &pixmap)
{

    ShapeItem shapeItem;
    shapeItem.setPath( path );
    shapeItem.setToolTip( toolTip );
    shapeItem.setPosition( pos );
    shapeItem.setColor( color );
    shapeItem.setRecord( record);
    shapeItem.setPixmap ( pixmap );
    shapeItem.setType("İş Emri");
    shapeItems.append( shapeItem );

    update();
}

QToolButton *SortingBox::createToolButton(const QString &toolTip,
                                          const QIcon &icon,
                                          const char *member,
                                          const QString &text)
{
    QToolButton *button = new QToolButton(this);
    button->setToolTip(toolTip);
    button->setIcon(icon);
    button->setIconSize(QSize(32, 32));
    button->setText (text);
    button->setToolButtonStyle (Qt::ToolButtonStyle(2) );
    button->setAutoRaise (true);
    button->setWhatsThis ("WIT İş Emri");


    connect(button, SIGNAL(clicked()), this, member);
    return button;

}





int SortingBox::itemAt(const QPoint &pos)
{
    for (int i = shapeItems.size() - 1; i >= 0; --i) {
        const ShapeItem &item = shapeItems[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}


void SortingBox::moveItemTo(const QPoint &pos)
{
    QPoint offset = pos - previousPosition;
    itemInMotion->setPosition(itemInMotion->position() + offset);
    previousPosition = pos;
    update();
}



//int SortingBox::row(int i)
//{
//    static int row = 20;
//    qDebug() <<"row *****************************  "<< row;
//    // count

//    if ( i == 0 )
//    {
//        qDebug() <<"row 0  "<< row;
//        // row sıfırla
//        row = 20;
//        qDebug() <<"row 0  "<< row<<endl;
//    }
//    else if ( i == 1 )
//    {
//        // row  ayarla
//        qDebug() <<"row 1       : "<< row;
//        row+=180;
//        qDebug() <<"row 1 +180  : "<< row<<endl;

//    }

//    return row;

//}


//int SortingBox::col(int i)
//{
//    static int col = 65;
//    qDebug() <<"col *****************************  "<< col;

//    if ( i == 0 )
//    {
//        qDebug() <<"col 0  "<< col;
//        // col sıfırla
//        col = 65;
//        qDebug() <<"col 0  "<< col;
//    }
//    else if ( i == 1 )
//    {
//        // row col ayarla
//        qDebug() <<"col 1        : "<< col;
//        col +=110;
//        if (col >500)
//        {
//            col=20;
//       //     row+=180;
//        }
//      //  qDebug() <<"row +180     : "<< row;
//        qDebug() <<"col +110 =20 : "<< col<<endl;


//    }

//    return col;

//}

QPoint SortingBox::randomItemPosition()
{
    QPoint poss;
    int row = SortingBox::row  ;
    int col = SortingBox::col ;
    qDebug() <<"count(1,20)  : "<< SortingBox::row;
    qDebug() <<"count(1,30)  : "<< SortingBox::col;
    qDebug() <<"x yyyy        : "<< row <<":"<< col;

    SortingBox::col += 110 ;
    col = SortingBox::col;
    if (SortingBox::col>500)
    {
        SortingBox::row += 180;
        row = SortingBox::row;
        col =20;
        SortingBox::col = col;
    }
//    if (row>500)
//    {

//        row=70;
//        SortingBox::row=row;

//    }

    poss.rx() = row;
    poss.ry () = col;

    return poss;
    //return QPoint(QRandomGenerator::global()->bounded(width() - 120), QRandomGenerator::global()->bounded(height() - 120));
}

QColor SortingBox::initialItemColor()
{
    qDebug()<<" iic";
    return QColor::fromHsv(((shapeItems.size() + 1) * 85) % 256, 255, 190);
}


QColor SortingBox::randomItemColor()
{
    return QColor::fromHsv(QRandomGenerator::global()->bounded(256), 255, 190);
}


bool SortingBox::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        int index = itemAt(helpEvent->pos());
        if (index != -1)
        {
            QToolTip::showText(helpEvent->globalPos(), shapeItems[index].toolTip());
        } else
        {
            QToolTip::hideText();
            event->ignore();
        }

        if (event->type() == QEvent::ContextMenu)
        {


        }
        return true;
    }
    return QWidget::event(event);
}

void SortingBox::resizeEvent(QResizeEvent * /* event */ )
{
    //int margin = style()->pixelMetric(QStyle::PM_DefaultTopLevelMargin);
    //int x = width() - margin;
    //int y = height() - margin;


    //y = updateButtonGeometry(newSquareButton, x, y);
}


void SortingBox::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    foreach (ShapeItem const &shapeItem, shapeItems) {
        //! [8] //! [9]
        painter.translate(shapeItem.position());
        //! [9] //! [10]
        //painter.setBrush(shapeItem.color());
        painter.drawPath(shapeItem.path());
        painter.translate(-shapeItem.position());
        painter.setPen(Qt::darkBlue );
        painter.setFont(QFont("Arial", 12));
        /////// resim
        QRectF target(shapeItem.position().rx()+2,
                      shapeItem.position().ry()+27,
                      112.0, 70.0);
        QRectF source(0.0, 0.0, 336.0, 210.0);
        shapeItem.pixmap().setDevicePixelRatio (1);
        painter.drawPixmap(target, shapeItem.pixmap() , source);

        /////// ie rect
        QRect rectie(shapeItem.position().rx(),
                     shapeItem.position().ry(),
                     160, 25);

        painter.drawRoundedRect (rectie, 15, 15);
        painter.fillRect (rectie,QColor("#E08119"));
        painter.drawText(QPoint (shapeItem.position().rx()+5 ,
                                 shapeItem.position().ry()),
                         shapeItem.type());

        QSqlRecord x(shapeItem.record ());
        QString baslik = x.value (x.indexOf ("ie_no")).toString ()+" :: "+
                x.value (x.indexOf ("ie_mkn")).toString ();

        painter.drawText(QPoint (shapeItem.position().rx()+5 ,
                                 shapeItem.position().ry()+20), baslik);

        //qDebug ()<<"paint pixmap   = "<<shapeItem.pixmap();

    }
}
//! [10]

//! [11]
void SortingBox::mousePressEvent(QMouseEvent *event)
{
    //////////////////////////////////////////////  S A Ğ    T U Ş
    if (event->button() == Qt::RightButton)
    {
        int index = itemAt(event->pos());
        qDebug() <<"sağ tuş pos"<< event->pos ();
        if (index != -1) {
            itemInMotion = &shapeItems[index];
            previousPosition = event->pos();
            smSLOT (event->pos ());
            //shapeItems.move(index, shapeItems.size() - 1);
            //update();
            qDebug () << "epos = "
                         +QString::number (event->pos ().rx ())+","
                         +QString::number (event->pos ().ry ());

        }
    }
    if (event->button() == Qt::LeftButton)
    {
        int index = itemAt(event->pos());

        if (index != -1) {
            itemInMotion = &shapeItems[index];
            previousPosition = event->pos();
            shapeItems.move(index, shapeItems.size() - 1);
            update();
            qDebug () << "epos = "
                         +QString::number (event->pos ().rx ())+","
                         +QString::number (event->pos ().ry ());

        }
    }
}
//! [11]

//! [12]
void SortingBox::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && itemInMotion)
    {
        moveItemTo(event->pos());

    }
    QString x ="moved " + QString::number (event->pos().rx ())+
            +"-"+
            QString::number (event->pos().ry ());



}
//! [12]

//! [13]
void SortingBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && itemInMotion) {
        /*
        if (event->pos().x ()<=0)
        {
            pos().rx () = 0;
        }
        if (event->pos().y ()<=0)
        {
            pos().ry () = 0;
        }
*/
        this->setWindowTitle ("epos = "
                              +QString::number (event->pos ().rx ())+","
                              +QString::number (event->pos ().ry ())) ;

        moveItemTo(event->pos());
        //      moveItemTo(pos());
        pos()=event->pos ();
        itemInMotion = nullptr;
    }

}




void SortingBox::smSLOT(QPoint pos)
{
    //qDebug ()  <<"  cw mkn view sağ tuş 001";
    auto *menu = new QMenu(this);

    // sigorta kaydı ekle
    const QIcon ekleIc_sgrt = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_sgrt = new QAction(ekleIc_sgrt, tr("Sıra Bekliyor"), this);
    ekleAct_sgrt->setShortcuts (QKeySequence::New);
    ekleAct_sgrt->setStatusTip ("Sigorta Kaydı Ekle");
    connect (ekleAct_sgrt, &QAction::triggered,
             [this, pos]()
    {
        qDebug()<<"menu sıra bekliyor of kurum no"
               << itemAt(pos) << ""<< &shapeItems[itemAt(pos)] ;
    });

    menu->addAction(ekleAct_sgrt);

    // muayene kaydı ekle
    const QIcon ekleIc_mua = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_mua = new QAction(ekleIc_mua, tr("Usta Bekliyor"), this);
    ekleAct_mua->setShortcuts (QKeySequence::New);
    ekleAct_mua->setStatusTip ("Muayene Kaydı Ekle");
    connect (ekleAct_mua, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_mua);


    // yağ
    const QIcon ekleIc_yag = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_yag = new QAction(ekleIc_yag, tr("Parça Bekliyor"), this);
    ekleAct_yag->setShortcuts (QKeySequence::New);
    ekleAct_yag->setStatusTip ("Yağ Kaydı Ekle");
    connect (ekleAct_yag, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_yag);


    // filtre
    const QIcon ekleIc_flt = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_flt = new QAction(ekleIc_flt, tr("Tamamlandık"), this);
    ekleAct_flt->setShortcuts (QKeySequence::New);
    ekleAct_flt->setStatusTip ("Filtre Kaydı Ekle");
    connect (ekleAct_flt, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_flt);



    // yeni iş emri kaydı ekle
    const QIcon ekleIc_sipr = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_sipr = new QAction(ekleIc_sipr, tr("İş Emri Ekle..."), this);
    ekleAct_sipr->setShortcuts (QKeySequence::New);
    ekleAct_sipr->setStatusTip ("İş Emri Kaydı Ekle");
    connect (ekleAct_sipr, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_sipr);



    //  mkn kaydı SİL
    const QIcon silIc_mkn = QIcon(":/rsm/Erase.ico");
    QAction* silAct_mkn = new QAction(silIc_mkn, tr("Makina &Sil..."), this);
    silAct_mkn->setShortcuts (QKeySequence::New);
    silAct_mkn->setStatusTip ("DİKKAT :: Makina Kaydını ve bu makina ile ilgili herşeyi siler...");
    connect (silAct_mkn, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(silAct_mkn);

    menu->addSeparator();


    menu->popup(pos);
}

QPixmap SortingBox::getPixmap() const
{
    return pixmap;
}

void SortingBox::setPixmap(const QPixmap &value)
{
    pixmap = value;
}

QSqlRecord SortingBox::getCurrentRecord() const
{
    return currentRecord;
}

void SortingBox::setCurrentRecord(const QSqlRecord &value)
{
    currentRecord = value;
}




/* createShapeItem(squarePath, tr("Square"),
                 initialItemPosition(squarePath),
                 initialItemColor(),
                 "karecik",
                 QPixmap(":/images/ex.ico"));
*/


//    circlePath.addRect(QRect(0, 0, 240, 150));
/*    qreal x = trianglePath.currentPosition().x();
qreal y = trianglePath.currentPosition().y();
trianglePath.moveTo(x + 120 / 2, y);
trianglePath.lineTo(0, 100);
trianglePath.lineTo(120, 100);
trianglePath.lineTo(x + 120 / 2, y);
*/

/*    createShapeItem(circlePath, tr("Circle"),
                initialItemPosition(circlePath),
                initialItemColor(),
                "dairecik",
                QPixmap(":/images/ex.ico"));
*/

/*    createShapeItem(trianglePath, tr("Triangle"),
                initialItemPosition(trianglePath),
                initialItemColor(),
                "üçgencik",
                QPixmap(":/images/ex.ico"));
*/


//! [13]

//! [14]







/*    newCircleButton =
            createToolButton(tr("New Circle"),
                             QIcon(":/images/ex.ico"),
                             SLOT(createNewCircle()),
                             QPixmap(":/images/ex.ico"),
                             "Excavator");
*/

/*    newTriangleButton =
            createToolButton(tr("New Triangle"),
                             QIcon(":/images/excavator.png"),
                             SLOT(createNewTriangle()),
                             QPixmap(":/images/ex.ico"),
                             "tool üçgen");
*/
/*
    QPainter painter(this);
    QPen pen;  // creates a default pen
    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    //circlePath.addEllipse(QRect(0, 0, 100, 100));
    QPainterPath curvePath;
    curvePath.addRegion (QRegion
                         (QBitmap
                          (QPixmap(":/images/ex.ico"))) );
    // addEllipse(QRect(0, 0, 100, 100));
    QPainterPathStroker stroker;
    //        stroker.setCapStyle( Qt::RoundCap );
    //        stroker.setJoinStyle( Qt::RoundJoin  );
    //        stroker.setWidth( 3 );
    //        stroker.setCurveThreshold (.25);
    //        stroker.setDashPattern (Qt::SolidLine);
    circlePath = stroker.createStroke ( curvePath );
    //painter->drawPath( outline );
*/
//circlePath.addEllipse(QRect(0, 0, 100, 100));

/*
void SortingBox::createNewCircle()
{
    static int count = 1;
    createShapeItem(circlePath,
                    tr("Circle <%1>").arg(++count),
                    randomItemPosition(),
                    randomItemColor(),
                    "daire",
                    QPixmap(":/images/ex.ico"));
}
//! [14]
//! [15]
//! [15]
//! [16]
void SortingBox::createNewTriangle()
{
    static int count = 1;
    createShapeItem(trianglePath,
                    tr("Triangle <%1>").arg(++count),
                    randomItemPosition(),
                    randomItemColor(),
                    "üçgen",
                    QPixmap(":/images/ex.ico"));
}
//! [16]
//! [17]
*/


/*
SortingBox(QWidget *parent) :  QWidget(parent)
{
    Q_OBJECT
    public:
    SortingBox();
    protected:
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    private slots:
    void smSLOT(QPoint pos);
    void createNewSquare();
    //  void createNewTriangle();
    //! [0]
    //! [1]
    private:
    int updateButtonGeometry(QToolButton *button, int x, int y);
    void createShapeItem(const QPainterPath &path, const QString &toolTip,
                         const QPoint &pos,
                         const QColor &color,
                         const QString &text,
                         const QPixmap &pixmap);
    int itemAt(const QPoint &pos);
    void moveItemTo(const QPoint &pos);
    QPoint initialItemPosition(const QPainterPath &path);
    QPoint randomItemPosition();
    QColor initialItemColor();
    QColor randomItemColor();
    QToolButton *createToolButton(const QString &toolTip,
                                  const QIcon &icon,
                                  const char *member,
                                  const QPixmap &pixmap,
                                  const QString &text="2323");
    QList<ShapeItem> shapeItems;
    //    QPainterPath circlePath;
    QPainterPath squarePath;
    //  QPainterPath trianglePath;
    QPoint previousPosition;
    ShapeItem *itemInMotion;
    // QToolButton *newCircleButton;
    QToolButton *newSquareButton;
    //QToolButton *newTriangleButton;
}
*/

int SortingBox::updateButtonGeometry(QToolButton *button, int x, int y)
{
    QSize size = button->sizeHint();
    button->setGeometry(x - size.rwidth(), y - size.rheight(),
                        size.rwidth(), size.rheight());

    return y - size.rheight()
            - style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing);
}



QPoint SortingBox::initialItemPosition(const QPainterPath &path)
{
    qDebug()<<" iip";
    int x;
    int y = (height() - (int)path.controlPointRect().height()) / 2;
    if (shapeItems.size() == 0)
        x = ((3 * width()) / 2 - (int)path.controlPointRect().width()) / 2;
    else
        x = (width() / shapeItems.size()
             - (int)path.controlPointRect().width()) / 2;

    return QPoint(x, y);
}
