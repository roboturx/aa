
#include <QtWidgets>
#include <stdlib.h>
#include "sortingbox.h"

SortingBox::SortingBox()
{
    setMouseTracking(true);
    setBackgroundRole(QPalette::Base);
    itemInMotion = nullptr;
  //  setWindowTitle(tr("Makina İkmal Atölye Bakım Onarım Yönetim Programı"));
  //  resize(960, 600);
    newSquareButton =
            createToolButton(tr("Excavator"),
                             QIcon(":/rsm/ex.ico"),
                             SLOT(createNewSquare()),
                             QPixmap(":/rsm/ex.ico"),
                             "Excavator");

    squarePath.addRect(QRect(0, 0, 240, 150));
    /// bu fonksiyonun içinden kontrol edelim


}



void SortingBox::createNewSquare()
{
    static int count = 1;

    qDebug()<< "active 1";
    QSqlQuery query("SELECT * FROM ie_dbtb WHERE ie_durum != 'Tamamlandı'");

    if (query.isActive ())
    {
        qDebug()<< "active " ;
    }
    else {
        qDebug()<< "not active "<< query.lastError ().text ();
    }

    while (query.next()) {
        qDebug()<< "active 61 while next" ;


        qDebug()<<"2 "<< query.value(2).toString();
        qDebug()<<"4 "<< query.value(4).toString();



        createShapeItem(squarePath,
                        tr("Excavator < %1 >").arg(++count),
                        randomItemPosition(),
                        randomItemColor(),
                        QString::number (count)+"---"+query.value(2).toString(),
                        QPixmap(":/rsm/ex.ico"));
        if(query.value( 4 ).toString() == "Tamamlandı")
        {
            qDebug()<< "taamamlandı 612" ;
        }
        if(query.value( 4 ).toString() == "Sıra Bekliyor")
        {
            qDebug()<< "sırada 612" ;
        }
        if(query.value( 4 ).toString() == "Bakıma Alındı")
        {
            qDebug()<< "bakımda 612" ;
        }

    }

    qDebug()<< "active 7" ;


    //    createShapeItem(squarePath,
    //                    tr("Excavator < %1 >").arg(++count),
    //                    randomItemPosition(),
    //                    randomItemColor(),
    //                    "60-190001",
    //                    QPixmap(":/rsm/ex.ico"));
}



void SortingBox::createShapeItem(const QPainterPath &path,
                                 const QString &toolTip,
                                 const QPoint &pos,
                                 const QColor &color,
                                 const QString &text,
                                 const QPixmap &pixmap)
{
    ShapeItem shapeItem;
    shapeItem.setPath( path );
    shapeItem.setToolTip( toolTip );
    shapeItem.setPosition( pos );
    shapeItem.setColor( color );
    shapeItem.setText( text );
    shapeItem.setPixmap ( pixmap );
    shapeItems.append( shapeItem );
    update();
    shapeItem.setContextMenuPolicy (Qt::CustomContextMenu);
    connect(shapeItem, SIGNAL(customContextMenuRequested(QPoint)),
      this, SLOT(smSLOT(QPoint)));
}

QToolButton *SortingBox::createToolButton(const QString &toolTip,
                                          const QIcon &icon,
                                          const char *member,
                                          const QPixmap &pixmap,
                                          const QString &text)
{
    QToolButton *button = new QToolButton(this);
    button->setToolTip(toolTip);
    button->setIcon(icon);
    button->setIconSize(QSize(32, 32));
    button->setText (text);
    button->setToolButtonStyle (Qt::ToolButtonStyle(2) );
    button->setAutoRaise (true);
    button->setWhatsThis ("Exca");


    connect(button, SIGNAL(clicked()), this, member);
    return button;

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
             []()
    {
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

QPoint SortingBox::randomItemPosition()
{
    return QPoint(QRandomGenerator::global()->bounded(width() - 120), QRandomGenerator::global()->bounded(height() - 120));
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
        if (index != -1) {
            QToolTip::showText(helpEvent->globalPos(), shapeItems[index].toolTip());
        } else {
            QToolTip::hideText();
            event->ignore();
        }

        return true;
    }
    return QWidget::event(event);
}

void SortingBox::resizeEvent(QResizeEvent * /* event */ )
{
    int margin = style()->pixelMetric(QStyle::PM_DefaultTopLevelMargin);
    int x = width() - margin;
    int y = height() - margin;

    y = updateButtonGeometry(newSquareButton, x, y);
}


void SortingBox::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    foreach (ShapeItem shapeItem, shapeItems) {
        //! [8] //! [9]
        painter.translate(shapeItem.position());
        //! [9] //! [10]
        painter.setBrush(shapeItem.color());
        painter.drawPath(shapeItem.path());
        painter.translate(-shapeItem.position());
        painter.setPen(Qt::darkRed );
        painter.setFont(QFont("Arial", 14));

        painter.drawText(QPoint (shapeItem.position().rx()+5 ,
                                 shapeItem.position().ry()),
                         shapeItem.text());
        //    qDebug ()<<"paint teeext   = "<<shapeItem.text();



        QRectF target(shapeItem.position().rx(),
                      shapeItem.position().ry(),
                      240.0, 150.0);
        QRectF source(0.0, 0.0, 320.0, 200.0);
        shapeItem.pixmap().setDevicePixelRatio (0.5);
        painter.drawPixmap(target, shapeItem.pixmap() , source);


        //qDebug ()<<"paint pixmap   = "<<shapeItem.pixmap();

    }
}
//! [10]

//! [11]
void SortingBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
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
    qDebug () << &"moved "[event->pos().rx ()];
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
