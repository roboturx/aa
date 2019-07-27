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

        /// kayıt oluşturalım
        isEmri->tb_view->pB_ekle->clicked ();

        /// kayıdı rec e alalım
        /// rec ie_dbtb de ki kayıt
        /// rec objenin özellikleri belirleyecek
        QModelIndex ndx = isEmri->tb_view->table->currentIndex ();
        QSqlRecord dbrecor;
        dbrecor = isEmri->tb_model->record (ndx.row ());

        auto dbrecord = new QSqlRecord;
        dbrecord = &dbrecor;
        /////////////////////////// ie için makinayı secelim
        QDialog makinasec;

        QHBoxLayout xl ;
        makinasec.setLayout (&xl);
        mkn = new hC_MKN();
        mkn->tbsetup();
        xl.addWidget (mkn);
        //// seçim penceresinde makina seçilir
        /// yoksa yeni oluşturulur
        connect(mkn, &hC_MKN::sgnMkn,
                [this, dbrecord](QString krmNo) mutable
        {
            //  1   iş emri için kurum no
            (*dbrecord).setValue ("ie_mkn", krmNo);
            isEmri->tb_model->submitAll ();
        });

        qDebug () <<"rec ieno   :"<<(*dbrecord).value ("ie_no");
        qDebug () <<"rec mknno  :"<<(*dbrecord).value ("ie_mkn");
        makinasec.exec ();
        ///// makina seçildi yola devam
        /// objeyi oluştur

        isEmriYeni (*dbrecord);


    });

    QPushButton* lst = new QPushButton("Listele",this);
    lst->move (60,120);
    connect(lst, &QPushButton::clicked,
            [this]()
    {
        isEmriListele();
    });



}


void DragWidget::isEmriYeni(QSqlRecord record)
{
    // objeyi oluştur
    CustomButton *boatIcon = new CustomButton (this);


    boatIcon->setRecord(record);
    boatIcon->CBsetup ();
    boatIcon->setPixmap (QPixmap(":/images/boat.png"));
    boatIcon->move(100, 10);
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
        QSqlRecord record ;
        record = query.record();

        isEmriYeni ( record);
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
            child->close();
        } else
        {
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
    objNo= QString::number( this->getObjNo () );
    ieno = new QLabel ;
    kurumno = new QLabel ;
    resim = new QLabel;
    SimileIcon = QPixmap(":/rsm/ex.ico").toImage ();

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


void CustomButton::CBsetup()
{
    this->setMinimumSize (150,130);

    setIeno (getRecord ().value ("ie_no").toString ());
    setKurumno (getRecord ().value ("ie_mkn").toString ());
    qDebug ()<<"CBsetup getieno :"<<getIeno ()<<endl;
    qDebug ()<<"CBsetup getkno :"<<getKurumno ()<<endl;


    ieno->setText (getIeno());
    ieno->resize (60,20);
    ieno->setAttribute (Qt::WA_TransparentForMouseEvents);
    objNo+=  getIeno ();

    kurumno->resize (100,20);
    kurumno->setText ( getKurumno ());
    kurumno->setAttribute (Qt::WA_TransparentForMouseEvents);
    objNo+= getKurumno();
    /// record daki pixmapı kullanım kolaylığı için
    /// set get yapıp getpixmap a atalım
    usedPixmap ();

    resim->setPixmap (getPixmap() );

    resim->setMinimumSize (80,50);
    resim->setMaximumSize (80,50);
    resim->resize (80,50);
    resim->setAttribute (Qt::WA_TransparentForMouseEvents);

}




QPixmap CustomButton::usedPixmap()
{
    /////////////////////////////////////////////////////////////////////////////
    // obj resmini record dan alalım

    QPixmap outPixmap ;
    QByteArray outByteArray = record.value
            ("ie_resim").toByteArray ();
    qDebug () <<"---------------------------------------";
    qDebug () <<outByteArray;
     qDebug () <<"---------------------------------------";


    qDebug () <<"oute byte array null "<< (outByteArray == "null");

    if (outByteArray == "null")
    {

        qDebug () <<"oute byte array 1"<< (outByteArray == "null");
        outPixmap=QPixmap(":/rsm/ex.png");
    }
    else
    {
        qDebug () <<"oute byte array 2 "<< (outByteArray == "null");
                outPixmap.loadFromData ( outByteArray );
    }
    setPixmap(outPixmap);
    return outPixmap;
}

QPixmap CustomButton::getPixmap() const
{
    return pixmap;
}

void CustomButton::setPixmap(QPixmap value)
{
    pixmap = value;
}

CustomButton::~CustomButton()
{

}

QSqlRecord CustomButton::getRecord() const
{
    return record;
}

void CustomButton::setRecord(QSqlRecord value)
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
    return objNo.toInt ();
}

void CustomButton::setObjNo(int value)
{
    objNo = QString::number (value);
}




//Paint event of button
void CustomButton::paintEvent(QPaintEvent *paint)
{
    QPushButton::paintEvent(paint);
    QPainter painter(this);




    painter.save();
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::SmoothPixmapTransform,1);
    painter.scale (1,1) ;
    //  painter.drawText(QPoint(1,1),FirstName); //Simple Text.
    painter.setPen(Qt::blue);                       //changing the color of pen.
    painter.setFont(QFont("Arial", 12, QFont::Bold));     //Changing the font.





    /////////////////////////////////////////////////////////////////////////////
    // obj resmini record dan alalım

    QPixmap outPixmap = getPixmap ();


    // pixmap büyüklüğünü yazdıracağımız rect e ayarlayalım

    // const QPixmap outPixmap(outPixmap);

    QSize widgetSize = rect().size();
    const auto newHeight = widgetSize.width()*
            outPixmap.height()/outPixmap.width();
    if(newHeight<=widgetSize.height())
    {
        widgetSize.setHeight(newHeight);
    }
    else
    {
        widgetSize.setWidth(widgetSize.height()*
                            outPixmap.width()/outPixmap.height());
    }
    style()->drawItemPixmap(&painter,rect(),
                            Qt::AlignCenter,outPixmap.scaled(widgetSize));
    painter.drawPixmap (rect (),outPixmap);
    /////////////////////////////////////////////////////////////////////////////
    /// \brief xR
    /// üst satıra ie no ve kurumnoyu yazalım
    QRect xR(0,0,150,16);
    painter.drawRect (xR);
    painter.fillRect (xR, QBrush (QColor(34,34,234,234)));

    painter.setPen(Qt::cyan);
    painter.drawText(rect(), Qt::AlignTop, objNo);
    painter.restore();
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
