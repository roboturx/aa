#include "dragwidget.h"


int DragWidget::count=1;
int DragWidget::col=20;
int DragWidget::row=65;



DragWidget::DragWidget(QWidget *parent)
    : QWidget(parent)
{
    //setMinimumSize(200, 200);
    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    isEmri = new hC_IE;
    isEmri->tbsetup ();
    isEmri->hide ();



    QPushButton* yeni = new QPushButton("Yeni",this);
    yeni->move (60,60);
    connect(yeni, &QPushButton::clicked,
            [this]()
    {

        // kayıt oluşturalım
       // isEmri->tb_view->pB_ekle->click ();
        isEmri->tb_view->cB_map->
             setCheckState (Qt::PartiallyChecked);
        isEmri->show ();




        QSqlQuery query("SELECT * FROM ie_dbtb "
                        "WHERE ie_durum != 'Tamamlandı'");
        if (query.isActive ())
        {
            qDebug()<< "active " ;
        }
        else {
            qDebug()<< "not active "<< query.lastError ().text ();
        }

        while (query.next())
        {
            if (query.value (1) == 0 )
            {
            auto outPixmap = new QPixmap ;
            outPixmap->loadFromData( query.value (9).toByteArray () );
            auto record = new QSqlRecord;
            *record = query.record();

            isEmriYeni ( outPixmap, record);
            }
        }

    });

    QPushButton* lst = new QPushButton("Listele",this);
    lst->move (60,120);
    connect(lst, &QPushButton::clicked,
            [this]()
    {
       isEmriListele();
    });



}


void DragWidget::isEmriYeni(QPixmap* pixmap, QSqlRecord* record)
{



    CustomButton *boatIcon = new CustomButton (this);
    boatIcon->resim->setPixmap ( *pixmap );
    boatIcon->setRecord(record);
    boatIcon->move(10, 10);
    boatIcon->show();
    boatIcon->setAttribute(Qt::WA_DeleteOnClose);

}



void DragWidget::isEmriListele()
{

    ///// toolbutton için
    ////////////////// iş emirlerini ekrana listele
    DragWidget::count = 0 ;
    DragWidget::row = 65 ;
    DragWidget::col = 20 ;
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
        auto outPixmap = new QPixmap ;
        outPixmap->loadFromData( query.value (9).toByteArray () );
        auto record = new QSqlRecord;
        *record = query.record();

        isEmriYeni ( outPixmap, record);
    }

}


void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        static int noo=1;

        CustomButton *newIcon = new CustomButton(this);
        newIcon->resim->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->setObjNo (noo++);
        newIcon->show();
        int xx = newIcon->getObjNo ();

        newIcon->setToolTip (QString::number (xx) );
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this)
        {
            qDebug ()<<"event accepted in drop";
            event->setDropAction(Qt::MoveAction);
            event->accept();

        } else
        {
            qDebug ()<<"event NOT accepted in drop";
            event->acceptProposedAction();
        }
    } else
    {
        event->ignore();
    }
}

//! [1]
void DragWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button () == Qt::LeftButton )
    {

        ///burada child olarak alınıyor
        CustomButton *child = static_cast< CustomButton *>(childAt(event->pos()));
        qDebug ()<<"child at pos "<< childAt(event->pos());
        qDebug ()<<"child        "<< child;
        if (!child)
            return;
        QPixmap pixmap = *child->resim->pixmap();

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << QPoint(event->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();

        ////child->label->setPixmap(tempPixmap);

        if (drag->exec(Qt::CopyAction
                       | Qt::MoveAction,
                       Qt::CopyAction) == Qt::MoveAction)

        {
            qDebug ()<<"child closed";
            child->close();
        } else
        {
            qDebug ()<<"child showed";
            child->show();
            child->resim->setPixmap(pixmap);
        }
    }

}



void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}



/////////////////////////////////////////////////////////
/// \brief CustomButton::CustomButton
/// \param parent
///
///
///
///

CustomButton::CustomButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setMinimumSize (150,130);

    No= QString::number( this->getObjNo () );

    ieno = new QLabel ;
    ieno->setText (getIeno());
    ieno->resize (60,20);
    ieno->setAttribute (Qt::WA_TransparentForMouseEvents);
    No+=ieno->text ();

    kurumno = new QLabel ;
    kurumno->resize (100,20);
    kurumno->setText ( getKurumno ());
    kurumno->setAttribute (Qt::WA_TransparentForMouseEvents);
    No+=kurumno->text ();

    qDebug ()<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa "
        <<endl<< this->record ;

    QByteArray outByteArray = this->record->
            value ("ie_resim").toByteArray ();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData ( outByteArray );

    resim = new QLabel;
    resim->setMinimumSize (80,50);
    resim->setPixmap (outPixmap);
    resim->resize (80,50);
    resim->setAttribute (Qt::WA_TransparentForMouseEvents);

    SimileIcon = QPixmap(":/images/boat.png").toImage ();

    QToolButton* x1 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x1->setIconSize (QSize(40,25));
    x1->setAutoRaise (true);
    connect (x1, &QToolButton::clicked, this,
             &CustomButton::smSLOT );

    QToolButton* x2 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x2->setIconSize (QSize(40,25));
    x2->setAutoRaise (true);
    connect (x2, &QToolButton::clicked, this,
             &CustomButton::smSLOT );

    QToolButton* x3 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x3->setIconSize (QSize(40,25));
    x3->setAutoRaise (true);
    connect (x3, &QToolButton::clicked, this,
             &CustomButton::smSLOT );

    QToolButton* x4 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x4->setIconSize (QSize(40,25));
    x4->setAutoRaise (true);
    connect (x4, &QToolButton::clicked, this,
             &CustomButton::smSLOT );


   // x->move (50,50);
auto gr = new QGridLayout(this);

//gr->addWidget (resim    ,0 ,3 ,5 , 3 );

gr->addWidget (x1       ,1 ,0 ,2 , 2 );
gr->addWidget (x2       ,2 ,0 ,2 , 2 );
gr->addWidget (x3       ,3 ,0 ,2 , 2 );
gr->addWidget (x4       ,4 ,0 ,2 , 2 );


}

CustomButton::~CustomButton()
{

}

QSqlRecord *CustomButton::getRecord() const
{
    return record;
}

void CustomButton::setRecord(QSqlRecord *value)
{
    record = value;
}



void CustomButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button () == Qt::RightButton )
    {
        smSLOT (/*event->pos ()*/);
    }
    else
    {
    event->ignore ();
    }
}

QString CustomButton::getKurumno() const
{
    return kurumno->text ();
}

void CustomButton::setKurumno(QString value)
{
    kurumno->setText ( value ) ;
}

QString CustomButton::getIeno() const
{
    return ieno->text ();
}

void CustomButton::setIeno(QString value)
{
    ieno->setText (value);
}

int CustomButton::getObjNo() const
{
    return objNo;
}

void CustomButton::setObjNo(int value)
{
    objNo = value;
}




//Paint event of button
void CustomButton::paintEvent(QPaintEvent *paint)
{
    QPushButton::paintEvent(paint);
    QPainter p(this);
    p.save();

  //  p.drawText(QPoint(1,1),FirstName); //Simple Text.
    p.setPen(Qt::blue);                       //changing the color of pen.
    p.setFont(QFont("Arial", 12, QFont::Bold));     //Changing the font.

    QRect xR(0,0,150,16);
    p.drawRect (xR);
    p.fillRect (xR, QBrush (QColor(34,34,234,234)));

        p.setPen(Qt::cyan);
        p.drawText(rect(), Qt::AlignTop, No);

  //  p.drawText(QPoint( 5, 15),No);
    p.drawImage(QPoint(60, 30),SimileIcon);
    p.restore();
}



//QLabel *carIcon = new QLabel(this);
//carIcon->setPixmap(QPixmap(":/images/car.png"));
//carIcon->move(100, 10);
//carIcon->show();
//carIcon->setAttribute(Qt::WA_DeleteOnClose);

//QLabel *houseIcon = new QLabel(this);
//houseIcon->setPixmap(QPixmap(":/images/house.png"));
//houseIcon->move(10, 80);
//houseIcon->show();
//houseIcon->setAttribute(Qt::WA_DeleteOnClose);

void CustomButton::smSLOT()
{
    //qDebug ()  <<"  cw mkn view sağ tuş 001";
    auto *menu = new QMenu(this);

    // sigorta kaydı ekle
    const QIcon ekleIc_sgrt = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_sgrt = new QAction(ekleIc_sgrt, tr("Sıra Bekliyor"), this);
    ekleAct_sgrt->setShortcuts (QKeySequence::New);
    ekleAct_sgrt->setStatusTip ("Sigorta Kaydı Ekle");
    connect (ekleAct_sgrt, &QAction::triggered,
             [this]()
    {
        qDebug()<<"menu sıra bekliyor of kurum no"<< getObjNo ();
     //          << itemAt(pos) << ""<< &shapeItems[itemAt(pos)] ;
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

QPoint pos(50,50);
    menu->popup(pos);
}
