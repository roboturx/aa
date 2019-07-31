#include "dragwidget.h"



int DragWidget::count=1;
int DragWidget::col=20;
int DragWidget::row=65;

DragWidget::DragWidget(QWidget *parent) : QWidget (parent)
{
    setAcceptDrops(true);
}

void IEcard::setDefaults(/*QSqlRecord record*/)
{

    qDebug()<< "rec before booticon set defaults---------------" ;
    qDebug()<< "while no " << record.value ("ie_no");
    qDebug()<< "mkn no   " << record.value ("ie_mkn");
    qDebug()<< "drm      " << record.value ("ie_durum");
    qDebug()<< "trh      " << record.value ("ie_tarih");
    qDebug()<< "rsmie    " << record.value ("ie_resimie").toString ().size ();
    qDebug()<< "rsmmkn   " << record.value ("ie_resimmkn").toString ().size ();

    IEcard::setIeno    (getRecord ().value ("ie_no" ).toString ());
    IEcard::setKurumno (getRecord ().value ("ie_mkn").toString ());

    /// obj başlığında
    /// 1- obj no = obj sayısını belirler
    /// 2- ieno
    /// 3- kurumno

    IEcard::paintObjNo = QString::number (getObjNo () );
    IEcard::paintObjNo+= " "+ getIeno () +" ";
    IEcard::paintObjNo+= getKurumno();

    /// resimler QByteArray olarak record da kayıtlı
    /// bunu Qpixmap çevirip getpixmap de pixmap
    /// olarak saklıyoruz
    /// record daki pixmapı kullanım kolaylığı için
    /// set get yapıp getpixmap a atalım
    IEcard::usedPixmapie ();
    IEcard::usedPixmapmkn ();

    IEcard::resim->setPixmap (getPixmapmkn() );
    IEcard::resim->setMinimumSize (80,50);
    IEcard::resim->setMaximumSize (80,50);
    IEcard::resim->resize (80,50);
    IEcard::resim->setAttribute (Qt::WA_TransparentForMouseEvents);

    IEcard::setAttribute(Qt::WA_DeleteOnClose);
    IEcard::move(100, 10);
    IEcard::show();
    qDebug()<< "rec after booticon set defaults---------------" ;
    qDebug()<< "while no " << record.value ("ie_no");
    qDebug()<< "mkn no   " << record.value ("ie_mkn");
    qDebug()<< "drm      " << record.value ("ie_durum");
    qDebug()<< "trh      " << record.value ("ie_tarih");
    qDebug()<< "rsmie    " << record.value ("ie_resimie").toString ().size ();
    qDebug()<< "rsmmkn   " << record.value ("ie_resimmkn").toString ().size ();


}






void DragWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button () == Qt::LeftButton )
    {

        ///burada child olarak alınıyor
        IEcard *child = static_cast< IEcard *>(childAt(event->pos()));
        if (!child)
            return;

        int     objno     { child->getObjNo     () } ;
        QString paintObjno{ child->getPaintObjNo() } ;
        QString ieno      { child->getIeno      () } ;
        QString kurumno   { child->getKurumno   () } ;
        QPixmap pixmapie  { child->getPixmapie  () } ;
        QPixmap pixmapmkn { child->getPixmapmkn () } ;

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        dataStream << objno
                   << paintObjno
                   << ieno
                   << kurumno
                   << pixmapie
                   << pixmapmkn
                   << QPoint(event->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        /// taşıma sırsındaki pixmap
        //  drag->setPixmap(pixmapmkn);

        ///resmin küçüğününü yap
        QPixmap tempPixmap = pixmapmkn;
        //        QPixmap pix(160,100);
        //        QPainter p(&pix);
        //        p.restore ();
        //        p.drawPixmap (QRect (0,0,160,100),tempPixmap);
        //        p.drawText(QPoint(10 ,10),"text");
        //        p.save();


        //        drag->setPixmap(pix);
        drag->setPixmap(pixmapmkn.scaled(160,100,Qt::KeepAspectRatio));

        drag->setHotSpot(event->pos()- child->pos());
        tempPixmap = pixmapmkn;
        QPainter painter;
        painter.begin(&tempPixmap);

        // tempPixmap.scaled (QSize(510,510),Qt::IgnoreAspectRatio);
        // painter.fillRect(tempPixmap.rect(), QColor(127, 127, 127, 127));
        painter.drawPixmap (rect (),tempPixmap);
        painter.end();
        // child->setPixmapmkn(tempPixmap);

        if (drag->exec(Qt::CopyAction
                       | Qt::MoveAction,
                       Qt::CopyAction) == Qt::MoveAction)
        {
            child->close();
        } else
        {
            child->show();
            child->setPixmapmkn(tempPixmap);
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



void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        //        ///burada child olarak alınıyor
        //        IEcard *child = static_cast< IEcard *>(childAt(event->pos()));
        //        if (!child)
        //            return;

        int objno;
        QString paintObjNo;
        QString ieno ;
        QString kurumno ;
        QPixmap pixmapie ;
        QPixmap pixmapmkn ;
        QSqlRecord record ;
        QPoint offset;

        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");

        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        dataStream >> objno
                >> paintObjNo
                >> ieno
                >> kurumno
                >> pixmapie
                >> pixmapmkn
                >> offset;
        IEcard *newIcon = new IEcard(this);
        newIcon->move(event->pos() - offset);
        newIcon->setObjNo ( objno);
        newIcon->setPaintObjNo ( paintObjNo);
        newIcon->setIeno(ieno) ;
        newIcon->setKurumno(kurumno) ;
        newIcon->setPixmapie(pixmapie) ;
        newIcon->setPixmapmkn(pixmapmkn) ;
        newIcon->resim->setPixmap (pixmapmkn);
        //newIcon->setRecord ();
        newIcon->show();
        //// eşitle
        ///
        //newIcon->setIeno (child->getIeno ());
        // newIcon->setObjNo (child->getObjNo ());
        // newIcon->setPixmap (pixmap);
        //        newIcon->setRecord (child->getRecord ());
        // newIcon->setKurumno (child->getKurumno ());


        newIcon->setToolTip (QString::number (newIcon->getObjNo ()) );
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();

        } else
        {
            event->acceptProposedAction();
        }
    } else
    {
        event->ignore();
    }

}



/////////////////////////////////////////////////////////
/// \brief IEcard::IEcard
/// \param parent
///
///
///
///

IEcard::IEcard(QWidget *parent)
    : DragWidget (parent)
{
    static int objn=1;
    objn++;
    this->setObjNo (objn);

    paintObjNo= QString::number( this->getObjNo () );

    resim = new QLabel;
    SimileIcon = QPixmap(":/rsm/ex.ico").toImage ();

    this->setMinimumSize (150,130);


    QToolButton* x1 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x1->setIconSize (QSize(25,25));
    x1->setAutoRaise (true);
    connect (x1, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x2 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x2->setIconSize (QSize(25,25));
    x2->setAutoRaise (true);
    connect (x2, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x3 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x3->setIconSize (QSize(25,25));
    x3->setAutoRaise (true);
    connect (x3, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x4 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x4->setIconSize (QSize(25,25));
    x4->setAutoRaise (true);
    connect (x4, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    // x->move (50,50);
    auto gr = new QGridLayout(this);

    //gr->addWidget (resim    ,0 ,3 ,5 , 3 );

    gr->addWidget (x1       ,1 ,0 ,2 , 2 );
    //gr->addWidget (isEmriDetay ,2 ,0 ,2 , 2 );
    gr->addWidget (x3       ,3 ,0 ,2 , 2 );
    gr->addWidget (x4       ,4 ,0 ,2 , 2 );



}




//Paint event of button
void IEcard::paintEvent(QPaintEvent *paint)
{
    QWidget::paintEvent(paint);
    QPainter painter(this);

    painter.save();
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::SmoothPixmapTransform,1);
    painter.scale (1,1) ;
    painter.setPen(Qt::blue);                       //changing the color of pen.
    painter.setFont(QFont("Arial", 12, QFont::Bold));     //Changing the font.
    /////////////////////////////////////////////////////////////////////////////
    /// resim mkn çizelim
    QPixmap outPixmap = getPixmapmkn ();

    QPoint rr(rect ().x()+25,rect ().y()+25 );
    painter.drawPixmap ( rr ,outPixmap.scaled(120,75,Qt::KeepAspectRatio));
    /////////////////////////////////////////////////////////////////////////////
    /// üst satıra ie no yu yazalım
    QRect UstRect(0,0,150,24);
    painter.drawRect (UstRect);
    painter.fillRect (UstRect, QBrush (QColor(60,60,60,234)));
    painter.setPen(Qt::cyan);
    painter.drawText(UstRect, Qt::AlignHCenter | Qt::AlignCenter,
                     " İş Emri #: "+getIeno ());
    /////////////////////////////////////////////////////////////////////////////
    /// üst satıra kurumnoyu yazalım
    QRect altRect(rect ().x(),rect ().y()+105,
                  150,24);
    painter.drawRect (altRect);
    painter.fillRect (altRect, QBrush (QColor(60,60,60,224)));

    painter.setPen(Qt::green);
    painter.drawText(altRect, Qt::AlignHCenter | Qt::AlignCenter,
                     " "+getKurumno ());
    painter.restore();
}



void IEcard::mousePressEvent(QMouseEvent *event)
{
    if (event->button () == Qt::RightButton )
    {
        smSLOT ();
    }
    else
    {
        event->ignore ();

    }
    if (event->button () == Qt::LeftButton )
    {
        event->ignore ();

    }
}


void IEcard::smSLOT()
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

    // QPoint pos(50,50);
    menu->popup(this->pos ());
}






QPixmap IEcard::usedPixmapmkn()
{
    qDebug () <<"100 usedpixmapmkn------------------------------";
    QPixmap outPixmapmkn ;
    outPixmapmkn=QPixmap(":/rsm/logo/Audi.png");

    QByteArray outByteArray = record.value
            ("ie_resimmkn").toByteArray ();
    qDebug () <<" 101 bytearray mkn in used size  "<<outByteArray.size ();
    qDebug () <<" 102 outpixmkn şu anda audi size "<<outPixmapmkn.size ();
    qDebug () <<" 103 outbytearray               "<<outByteArray ;
    if (outByteArray != "null" || outByteArray != "")
    {
         qDebug () <<"   outbytearray boş deil loadromdat";
        outPixmapmkn.loadFromData ( outByteArray );
    }

    setPixmapmkn(outPixmapmkn);

    qDebug () <<"  111 outbytearray mkn  size "<<outByteArray.size ();
    qDebug () <<"  112 outpixmkn deüişti mi    "<<outPixmapmkn.size ();
    qDebug () <<"  113 outpixmkn           "<<outPixmapmkn;
    qDebug () <<"  1131 getpixmaapmkn size "<< getPixmapmkn().size () ;
    qDebug () <<"usedpixmapmkn-------sonu--------------------";
    return outPixmapmkn;
}


QPixmap IEcard::usedPixmapie()
{
    QPixmap outPixmapie ;
    outPixmapie=QPixmap(":/rsm/logo/Audi.png");
    QByteArray outByteArray = record.value
            ("ie_resimie").toByteArray ();
    qDebug () <<"out bytearray ie  "<<outByteArray.size ();
    qDebug () <<"out pix ie şu anda audi "<<outPixmapie.size ();
    if (outByteArray != "null" || outByteArray == "")
    {
        outPixmapie.loadFromData ( outByteArray );
    }
    setPixmapie(outPixmapie);
    qDebug () <<"out pix ie "<<outPixmapie;
    return outPixmapie;
}


QPixmap IEcard::getPixmapie() const
{
    return pixmapie;
}

void IEcard::setPixmapie(QPixmap value)
{
    pixmapie = value;
}

IEcard::~IEcard()
{

}

QString IEcard::getPaintObjNo() const
{
    return paintObjNo;
}

void IEcard::setPaintObjNo(const QString &value)
{
    paintObjNo = value;
}

QPixmap IEcard::getPixmapmkn() const
{
    return pixmapmkn;
}

void IEcard::setPixmapmkn(const QPixmap &value)
{
    pixmapmkn = value;
}

QSqlRecord IEcard::getRecord() const
{
    return record;
}

void IEcard::setRecord(QSqlRecord value)
{
    record = value;
}




QString IEcard::getKurumno() const
{
    return kurumno;
}

void IEcard::setKurumno(QString value)
{
    kurumno = value  ;
}

QString IEcard::getIeno() const
{
    return ieno;
}

void IEcard::setIeno(QString value)
{
    ieno = value ;
}

int IEcard::getObjNo() const
{
    return objNo ;
}

void IEcard::setObjNo(int value)
{
    objNo = value;
}

