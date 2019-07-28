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
                [this, dbrecord](QString krmNo, QByteArray byteArray) mutable
        {
            //  1   iş emri için kurum no
            (*dbrecord).setValue ("ie_mkn", krmNo);
            // signal dan gelen byte array
            (*dbrecord).setValue ("ie_resimmkn", byteArray );
            qDebug () <<"rec ieno   :"<<(*dbrecord).value ("ie_no");
            qDebug () <<"rec mknno  :"<<(*dbrecord).value ("ie_mkn");

            isEmri->tb_model->submitAll ();
        });
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
    /// objeyi oluştur


    IEcard *boatIcon = new IEcard (this);

    ///objeyi olşturduk ie özelliklerini içine atalım
    /// burada table dan direk okuma yerine
    /// table recordu objenin içine yerleştirdik
    /// obje oluştuğunda table ile bağlantısı kalmıyor
    /// record zaten içinde
    boatIcon->setRecord(record);

    /// özellikleri içinden alıp objeyi oluşturalım
    boatIcon->setDefaults ();

}



void IEcard::setDefaults()
{

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
    // qDebug () <<"recorda eklenen pix  : "<<getPixmap();
    IEcard::resim->setMinimumSize (80,50);
    IEcard::resim->setMaximumSize (80,50);
    IEcard::resim->resize (80,50);
    IEcard::resim->setAttribute (Qt::WA_TransparentForMouseEvents);

    IEcard::setAttribute(Qt::WA_DeleteOnClose);
    IEcard::move(100, 10);
    IEcard::show();

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
        outPixmap->loadFromData( query.value ("ie_resim").toByteArray () );
        QSqlRecord record ;
        record = query.record();

        isEmriYeni ( record);
    }

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
qDebug ()<<"drag begins";
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        /// taşıma sırsındaki pixmap
      //  drag->setPixmap(pixmapmkn);

        void DrawImage()
        {
              QPixmap pix(700,700);
              QPainter painter(&pix);
              painter.drawText(QPoint(0 ,0),"text");
              painter.save();
              labelPixmap->setPixmap(pix);
        }
        ///resmin küçüğününü yap

        drag->setPixmap(pixmapmkn.scaled(100,100,Qt::KeepAspectRatio));

        drag->setHotSpot(event->pos()- child->pos());
qDebug ()<<"drag temppixmap";
        QPixmap tempPixmap = pixmapmkn;
        qDebug ()<<pixmapmkn;
        QPainter painter;
        painter.begin(&tempPixmap);

       // tempPixmap.scaled (QSize(510,510),Qt::IgnoreAspectRatio);
       // painter.fillRect(tempPixmap.rect(), QColor(127, 127, 127, 127));
        painter.drawPixmap (rect (),tempPixmap);
        painter.end();
qDebug ()<<"drag temppixmap ends";
      // child->setPixmapmkn(tempPixmap);

        if (drag->exec(Qt::CopyAction
                       | Qt::MoveAction,
                       Qt::CopyAction) == Qt::MoveAction)

        {
            qDebug ()<<"drag temppixmap ends 1111";
            child->close();
        } else
        {
            qDebug ()<<"drag temppixmap ends  22222";
            child->show();
            qDebug ()<<"//?????????????????????????";
            qDebug ()<<"child setpixmapé";
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
        qDebug ()<<"itemdata------------------";
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        qDebug ()<<"datastream------------------";
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        qDebug ()<<"datastream >> ------------------";
        dataStream >> objno
                   >> paintObjNo
                   >> ieno
                   >> kurumno
                   >> pixmapie
                   >> pixmapmkn
                   >> offset;
qDebug ()<<"new icon --------------------------------";
        IEcard *newIcon = new IEcard(this);
        newIcon->move(event->pos() - offset);
        newIcon->setObjNo ( objno);
        newIcon->setPaintObjNo ( paintObjNo);
        newIcon->setIeno(ieno) ;
        newIcon->setKurumno(kurumno) ;
        newIcon->setPixmapie(pixmapie) ;
        newIcon->setPixmapmkn(pixmapmkn) ;
        newIcon->resim->setPixmap (pixmapmkn);
     //   newIcon->setrecord ;
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
            qDebug ()<<"event accepted in drop source-----------";
            event->setDropAction(Qt::MoveAction);
            event->accept();

        } else
        {
             qDebug ()<<"event accepted in drop proposed------------";
            event->acceptProposedAction();
        }
    } else
    {
        qDebug ()<<"event NOT accepted in drop**********************";
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
    : QPushButton(parent)
{
    static int objn=1;
    objn++;
    this->setObjNo (objn);

    paintObjNo= QString::number( this->getObjNo () );

    resim = new QLabel;
    SimileIcon = QPixmap(":/rsm/ex.ico").toImage ();

    this->setMinimumSize (150,130);


    /*    QToolButton* x1 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x1->setIconSize (QSize(40,25));
    x1->setAutoRaise (true);
    connect (x1, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x2 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x2->setIconSize (QSize(40,25));
    x2->setAutoRaise (true);
    connect (x2, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x3 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x3->setIconSize (QSize(40,25));
    x3->setAutoRaise (true);
    connect (x3, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x4 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x4->setIconSize (QSize(40,25));
    x4->setAutoRaise (true);
    connect (x4, &QToolButton::clicked, this,
             &IEcard::smSLOT );
*/

    // x->move (50,50);
    auto gr = new QGridLayout(this);

    //gr->addWidget (resim    ,0 ,3 ,5 , 3 );
    /*
    gr->addWidget (x1       ,1 ,0 ,2 , 2 );
    gr->addWidget (x2       ,2 ,0 ,2 , 2 );
    gr->addWidget (x3       ,3 ,0 ,2 , 2 );
    gr->addWidget (x4       ,4 ,0 ,2 , 2 );

*/

}




//Paint event of button
void IEcard::paintEvent(QPaintEvent *paint)
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

    QPixmap outPixmap = getPixmapmkn ();
    painter.drawPixmap (rect (),outPixmap);
    /////////////////////////////////////////////////////////////////////////////
    /// üst satıra ie no ve kurumnoyu yazalım
    QRect xR(0,0,150,16);
    painter.drawRect (xR);
    painter.fillRect (xR, QBrush (QColor(34,34,234,234)));

    painter.setPen(Qt::cyan);
    painter.drawText(rect(), Qt::AlignTop, getPaintObjNo());
    painter.restore();
}



void IEcard::mousePressEvent(QMouseEvent *event)
{
    if (event->button () == Qt::RightButton )
    {
        smSLOT (/*event->pos ()*/);
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

    QPoint pos(50,50);
    menu->popup(pos);
}






QPixmap IEcard::usedPixmapmkn()
{
    /////////////////////////////////////////////////////////////////////////////
    // obj resmini record dan alalım

    QPixmap outPixmapmkn ;
    QByteArray outByteArray = record.value
            ("ie_resimmkn").toByteArray ();
    qDebug () <<"outbytearray"<<outByteArray;
    if (outByteArray == "null" || outByteArray == "")
    {
        outPixmapmkn=QPixmap(":/rsm/logo/Audi.png");
        qDebug () << "usedpix  mkn     audi     recorda eklendi";
    }
    else
    {
        outPixmapmkn.loadFromData ( outByteArray );
        setPixmapmkn(outPixmapmkn);
        qDebug () << "usedpix ie_mknresim recorda eklendi";
    }

    return outPixmapmkn;
}


QPixmap IEcard::usedPixmapie()
{
    /////////////////////////////////////////////////////////////////////////////
    // obj resmini record dan alalım

    QPixmap outPixmapie ;
    QByteArray outByteArray = record.value
            ("ie_resimie").toByteArray ();
    qDebug () <<"outbytearray"<<outByteArray;
    if (outByteArray == "null" || outByteArray == "")
    {
        outPixmapie=QPixmap(":/rsm/logo/Audi.png");
        qDebug () << "usedpix   ie    audi     recorda eklendi";
    }
    else
    {
        outPixmapie.loadFromData ( outByteArray );
        setPixmapmkn(outPixmapie);
        qDebug () << "usedpix ie_resimmkn recorda eklendi";
    }

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

