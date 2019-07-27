/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "dragwidget.h"

//! [0]
DragWidget::DragWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setAcceptDrops(true);

    CustomButton *boatIcon = new CustomButton (this);
    boatIcon->resim->setPixmap (QPixmap(":/images/boat.png"));
    boatIcon->move(10, 10);
    boatIcon->show();
    boatIcon->setAttribute(Qt::WA_DeleteOnClose);


}
//! [0]


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

    No= QString::number( this->getObjNo () );

    ieno = new QLabel ;
    ieno->resize (60,20);
    ieno->setText (": 035 :");
    ieno->setAttribute (Qt::WA_TransparentForMouseEvents);
    No+=ieno->text ();

    kurumno = new QLabel ;
    kurumno->resize (100,20);
    kurumno->setText ("19-200019");
    kurumno->setAttribute (Qt::WA_TransparentForMouseEvents);
    No+=kurumno->text ();

    pixmap = new QPixmap ;

    resim = new QLabel;
    resim->setMinimumSize (80,50);
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
    p.fillRect (xR, QBrush (QColor(34,34,34,234)));

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
