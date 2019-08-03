#include "dragwidget.h"


DragWidget::DragWidget(QWidget *parent) : QWidget (parent)
{
    setAcceptDrops(true);
    QPushButton* xyx2 = new QPushButton("Liste",this) ;
    xyx2->setIcon ( QIcon(":/rsm/ex.ico"));
    xyx2->setIconSize (QSize(25,25));
    //xyx2->setAutoRaise (true);
    connect (xyx2, &QToolButton::clicked,
             [this]()
    {
        emit sgnDragger();
    });

xyx2->move (0,0);

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
        int     ieno      { child->getIeno      () } ;
        QString kurumno   { child->getKurumno   () } ;
        QPixmap pixmapie  { child->getPixmapie  () } ;
        QPixmap dS_imagemkn { child->getPixmapmkn () } ;

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        dataStream << int(objno)
                   << QString(paintObjno)
                   << int(ieno)
                   << QString(kurumno)
                   << QPixmap(pixmapie)
                   << QPixmap(dS_imagemkn)
                   << QPoint(event->pos() - child->pos());



        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        ///resmin küçüğününü yap
        /// // dragger pixmap
        QPixmap tempPixmap = dS_imagemkn;
        drag->setPixmap(dS_imagemkn.scaled(160,100,Qt::KeepAspectRatio));
        drag->setHotSpot(event->pos() - child->pos());

        /// dragger pixmap painter
        /*QPainter painter;
    painter.save ();
       // painter.begin(&tempPixmap);
  //      painter.drawPixmap (rect (),tempPixmap);
      //  painter.end();
        painter.drawText ( 5, 20, "1. sıra yazı" );
        painter.drawText ( 5, 35, "2. sıra yazı" );
        painter.drawText ( 5, 50, "3. sıra yazı" );
        painter.drawText ( 5, 65, "4. sıra yazı" );
        painter.drawText ( 5, 80, "5. sıra yazı" );
painter.restore ();

*/
//child->setPixmapmkn(tempPixmap);

//        if (drag->exec(Qt::CopyAction  | Qt::MoveAction,
  //                     Qt::CopyAction) == Qt::MoveAction)
            if (drag->exec() == Qt::MoveAction)
        {
            child->close();
        }
        else
        {
            child->show();
        //    child->setPixmapmkn(tempPixmap);
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

        int objno;
        QString paintObjNo;
        int ieno ;
        QString kurumno ;
        QPixmap pixmapie ;
        QPixmap pixmapmkn ;
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

        IEcard *newIcon = new IEcard(ieno, this);
        newIcon->move(event->pos() - offset);
        newIcon->setObjNo ( objno);
        newIcon->setPaintObjNo ( paintObjNo);
        newIcon->setIeno(ieno) ;
        newIcon->setKurumno(kurumno) ;
        newIcon->setPixmapie(pixmapie) ;
        newIcon->setPixmapmkn(pixmapmkn) ;
        //newIcon->resim->setPixmap (pixmapmkn);
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
        if (event->source() == this )
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

IEcard::IEcard(int ieno, QWidget *parent) :
  QWidget(parent) //   : DragWidget (parent)
{

    this->setAcceptDrops (false); // ***
    this->setAttribute(Qt::WA_DeleteOnClose);




   // setIeno (ieno);
    static int objn=1;
    objn++;
    this->setObjNo (objn);


    QString kurumno_sT ;
    QPixmap dS_imagemkn;
    QPixmap dS_imageie;

    QFile file("isemri"+QString::number (ieno)+".dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading: "
                  << qPrintable(file.errorString()) << endl;
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_3);

    in  >> kurumno_sT
        >> dS_imagemkn
        >> dS_imageie;





    /// obj başlığında
    /// 1- obj no = obj sayısını belirler
    /// 2- ieno
    /// 3- kurumno


    IEcard::paintObjNo = QString::number (getObjNo () );
    IEcard::paintObjNo+= " "+QString::number ( getIeno ()) +" ";
    IEcard::paintObjNo+= getKurumno();

    IEcard::setIeno (ieno);
    IEcard::setKurumno (kurumno_sT);
    IEcard::setPixmapmkn (dS_imagemkn);
    IEcard::setPixmapie (dS_imageie);

//    /////////////////////////////////////////////////////////////////
//    auto x = new QDialog ;
//    x->setWindowTitle ("IECARD   ");
//    QPixmap xp;
//    auto xx = new QLabel ("3333333333333333333333");
//    auto xx1 = new QLabel ("3333333333333333333333");

//        xx1->setPixmap( getPixmapmkn ());


//    auto grd = new QVBoxLayout();
//    x->setLayout (grd);
//    grd->addWidget (xx1);
//    grd->addWidget (xx);
//    xx->setMinimumSize (QSize(160,100));

//    x->exec();

//    /////////////////////////////////////////////////////////////





//    resim = new QLabel;

//    IEcard::resim->setPixmap (getPixmapmkn() );
//    IEcard::resim->setMinimumSize (80,50);
//    IEcard::resim->setMaximumSize (80,50);
//    IEcard::resim->resize (80,50);
//    IEcard::resim->setAttribute (Qt::WA_TransparentForMouseEvents);

    IEcard::setAttribute(Qt::WA_DeleteOnClose);
    IEcard::move(100, 10);
    IEcard::show();

    this->setMinimumSize (150,130);




//    SimileIcon = QPixmap(":/rsm/ex.ico");
//    QToolButton* xxx1 = new QToolButton() ;
//    //x->setIcon ( QIcon(":/images/boat.png"));
//    xxx1->setIcon (QIcon( SimileIcon ));
//    xxx1->setIconSize (QSize(25,25));
//    xxx1->setAutoRaise (true);
//    connect (xxx1, &QToolButton::clicked, this,
//             &IEcard::smSLOT );

    QToolButton* x2 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x2->setIcon (QIcon(getPixmapmkn ()));
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

  //  gr->addWidget (xxx1       ,1 ,0 ,2 , 2 );
//    gr->addWidget ( resim   ,2 ,0 ,2 , 2 );
   // gr->addWidget (x3       ,3 ,0 ,2 , 2 );
   // gr->addWidget (x4       ,4 ,0 ,2 , 2 );



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
                     " "+ QString::number (getIeno ())+":"+getKurumno ());
    /////////////////////////////////////////////////////////////////////////////
    /// üst satıra kurumnoyu yazalım
    QRect altRect(rect ().x(),rect ().y()+105,
                  150,24);
    painter.drawRect (altRect);
    painter.fillRect (altRect, QBrush (QColor(60,60,60,224)));

    painter.setPen(Qt::green);
    painter.drawText(altRect, Qt::AlignHCenter | Qt::AlignCenter,
                     " İŞ EMRİ ");
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
        //delete this;
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

IEcard::~IEcard()
{
}

int IEcard::getObjNo() const
{    return objNo ; }
void IEcard::setObjNo(int value)
{    objNo = value; }

int IEcard::getIeno() const
{    return ieno; }
void IEcard::setIeno(int value)
{    ieno = value ; }

QString IEcard::getKurumno() const
{    return kurumno; }
void IEcard::setKurumno(QString value)
{    kurumno = value  ; }

QString IEcard::getPaintObjNo() const
{    return paintObjNo; }
void IEcard::setPaintObjNo(const QString value)
{    paintObjNo = value; }

QPixmap IEcard::getPixmapmkn() const
{    return pixmapmkn; }
void IEcard::setPixmapmkn(const QPixmap value)
{    pixmapmkn = value; }

QPixmap IEcard::getPixmapie() const
{    return pixmapie; }
void IEcard::setPixmapie(const QPixmap value)
{    pixmapie = value; }
