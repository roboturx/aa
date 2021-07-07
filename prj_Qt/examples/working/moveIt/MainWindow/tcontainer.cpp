#include "tcontainer.h"
#include <QApplication>

TContainer::TContainer(QWidget *parent, QPoint p, QWidget *cWidget) : QWidget(parent) {
    mode = NONE;
    childWidget = cWidget;
    setAttribute(Qt::WA_DeleteOnClose);
    this->setVisible(true);
    this->setAutoFillBackground(false);
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setFocus();
    this->move(p);

    vLayout = new QVBoxLayout(this);
    if (cWidget != 0) {
        cWidget->setParent(this);
        cWidget->releaseMouse();
        cWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        vLayout->addWidget(cWidget);
        vLayout->setContentsMargins(0, 0, 0, 0);
    }
    this->setLayout(vLayout);

    m_infocus = true;
    m_showMenu = false;
    m_isEditing = true;
    this->installEventFilter(parent);
}

TContainer::~TContainer() {
    delete vLayout;
}

void TContainer::setChildWidget(QWidget *cWidget) {
    if (cWidget != 0) {
        childWidget = cWidget;
        childWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        childWidget->setParent(this);
        vLayout->addWidget(cWidget);
        vLayout->setContentsMargins(0, 0, 0, 0);
    }
}

void TContainer::popupShow(const QPoint &pt) {
    if (menu->isEmpty()) return;
    QPoint global = this->mapToGlobal(pt);
    m_showMenu = true;
    menu->exec(global);
    m_showMenu = false;
}

void TContainer::focusInEvent(QFocusEvent *) {
    m_infocus = true;
    this->parentWidget()->installEventFilter(this);
    this->parentWidget()->repaint();
    emit inFocus(true);
}

void TContainer::focusOutEvent(QFocusEvent *) {
    if (!m_isEditing) return;
    if (m_showMenu) return;
    mode = NONE;
    emit outFocus(false);
    m_infocus = false;
}

bool TContainer::eventFilter(QObject *obj, QEvent *evt) {
    if (m_infocus) {
        QWidget *w = this->parentWidget();
        if (w == obj && evt->type() == QEvent::Paint) {
            // Draw container selection
            QPainter painter(w);
            QPoint p = this->mapTo(w, QPoint(-3, -3));
            QPoint LT = w->mapFrom(w, p);
            QPoint LB = w->mapFrom(w, QPoint(p.x(), p.y() + this->height()));
            QPoint RB = w->mapFrom(w, QPoint(p.x() + this->width(), p.y() + this->height()));
            QPoint RT = w->mapFrom(w, QPoint(p.x() + this->width(), p.y()));

            painter.fillRect(LT.x(), LT.y(), 6, 6, QColor("black"));
            painter.fillRect(LB.x(), LB.y(), 6, 6, QColor("black"));
            painter.fillRect(RB.x(), RB.y(), 6, 6, QColor("black"));
            painter.fillRect(RT.x(), RT.y(), 6, 6, QColor("black"));
            return QWidget::eventFilter(obj, evt);
        }
    }
    return QWidget::eventFilter(obj, evt);
}

void TContainer::mousePressEvent(QMouseEvent *e) {
    position = QPoint(e->globalX()-geometry().x(), e->globalY()-geometry().y());
    if (!m_isEditing) return;
    if (!m_infocus) return;
    if (!e->buttons() && Qt::LeftButton) {
        setCursorShape(e->pos());
        return;
    }
    if(e->button() == Qt::RightButton) {
        popupShow(e->pos());
        e->accept();
    }
}

void TContainer::keyPressEvent(QKeyEvent *e) {
    if (!m_isEditing) return;
    if (e->key() == Qt::Key_Delete) {
        this->deleteLater();
    }
    // Moving container with arrows
    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
        QPoint newPos(this->x(),this->y());
        if (e->key() == Qt::Key_Up) newPos.setY(newPos.y() - 1);
        if (e->key() == Qt::Key_Down) newPos.setY(newPos.y() + 1);
        if (e->key() == Qt::Key_Left) newPos.setX(newPos.x() - 1);
        if (e->key() == Qt::Key_Right) newPos.setX(newPos.x() + 1);
        move(newPos);
    }
    if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
        if (e->key() == Qt::Key_Up) resize(width(), height() - 1);
        if (e->key() == Qt::Key_Down) resize(width(), height() + 1);
        if (e->key() == Qt::Key_Left) resize(width() - 1, height());
        if (e->key() == Qt::Key_Right) resize(width() + 1, height());
    }
    emit newGeometry(this->geometry());
}

void TContainer::setCursorShape(const QPoint &e_pos) {
    const int diff = 3;
    if (
            //Left-Bottom
            ((e_pos.y() > y() + height() - diff) &&     //Bottom
             (e_pos.x() < x() + diff)) ||               //Left
            //Right-Bottom
            ((e_pos.y() > y() + height() - diff) &&     //Bottom
             (e_pos.x() > x() + width() - diff)) ||     //Right
            //Left-Top
            ((e_pos.y() < y() + diff) &&                //Top
             (e_pos.x() < x() + diff)) ||               //Left
            //Right-Top
            ((e_pos.y() < y() + diff) &&                //Top
             (e_pos.x() > x() + width() - diff))        //Right
            )
    {
        //Left-Bottom
        if ((e_pos.y() > y() + height() - diff) &&      //Bottom
                (e_pos.x() < x() + diff))               //Left
        {
            mode = RESIZEBL;
            setCursor(QCursor(Qt::SizeBDiagCursor));
        }
        //Right-Bottom
        if ((e_pos.y() > y() + height() - diff) &&      //Bottom
                (e_pos.x() > x() + width() - diff))     //Right
        {
            mode = RESIZEBR;
            setCursor(QCursor(Qt::SizeFDiagCursor));
        }
        //Left-Top
        if ((e_pos.y() < y() + diff) &&                 //Top
                (e_pos.x() < x() + diff))               //Left
        {
            mode = RESIZETL;
            setCursor(QCursor(Qt::SizeFDiagCursor));
        }
        //Right-Top
        if ((e_pos.y() < y() + diff) &&                 //Top
                (e_pos.x() > x() + width() - diff))     //Right
        {
            mode = RESIZETR;
            setCursor(QCursor(Qt::SizeBDiagCursor));
        }
    }
    // check cursor horizontal position
    else if ((e_pos.x() < x() + diff) ||                //Left
             ((e_pos.x() > x() + width() - diff)))      //Right
    {
        if (e_pos.x() < x() + diff) {                   //Left
            setCursor(QCursor(Qt::SizeHorCursor));
            mode = RESIZEL;
        } else {                                        //Right
            setCursor(QCursor(Qt::SizeHorCursor));
            mode = RESIZER;
        }
    }
    // check cursor vertical position
    else if (((e_pos.y() > y() + height() - diff)) ||   //Bottom
             (e_pos.y() < y() + diff))                  //Top
    {
        if (e_pos.y() < y() + diff) {                   //Top
            setCursor(QCursor(Qt::SizeVerCursor));
            mode = RESIZET;
        } else {                                        //Bottom
            setCursor(QCursor(Qt::SizeVerCursor));
            mode = RESIZEB;
        }
    } else {
        setCursor(QCursor(Qt::ArrowCursor));
        mode = MOVE;
    }
}

void TContainer::mouseReleaseEvent(QMouseEvent *e) {
    QWidget::mouseReleaseEvent(e);
}

void TContainer::mouseMoveEvent(QMouseEvent *e) {
    QWidget::mouseMoveEvent(e);
    if (!m_isEditing) return;
    if (!m_infocus) return;
    if (!e->buttons() && Qt::LeftButton) {
        QPoint p = QPoint(e->x() + geometry().x(), e->y() + geometry().y());
        setCursorShape(p);
        return;
    }

    if ((mode == MOVE || mode == NONE) && e->buttons() && Qt::LeftButton) {
        QPoint toMove = e->globalPos() - position;
        if (toMove.x() < 0) return;
        if (toMove.y() < 0) return;
        if (toMove.x() > this->parentWidget()->width() - this->width()) return;
        move(toMove);
        emit newGeometry(this->geometry());
        this->parentWidget()->repaint();
        return;
    }
    if ((mode != MOVE) && e->buttons() && Qt::LeftButton) {
        switch (mode){
        case RESIZETL: {    //Left-Top
            int newwidth = e->globalX() - position.x() - geometry().x();
            int newheight = e->globalY() - position.y() - geometry().y();
            QPoint toMove = e->globalPos() - position;
            resize(this->geometry().width() - newwidth, this->geometry().height() - newheight);
            move(toMove.x(), toMove.y());
            break;
        }
        case RESIZETR: {    //Right-Top
            int newheight = e->globalY() - position.y() - geometry().y();
            QPoint toMove = e->globalPos() - position;
            resize(e->x(), this->geometry().height() - newheight);
            move(this->x(), toMove.y());
            break;
        }
        case RESIZEBL: {    //Left-Bottom
            int newwidth = e->globalX() - position.x() - geometry().x();
            QPoint toMove = e->globalPos() - position;
            resize(this->geometry().width() - newwidth, e->y());
            move(toMove.x(), this->y());
            break;
        }
        case RESIZEB: {     //Bottom
            resize(width(), e->y());
            break;
        }
        case RESIZEL: {     //Left
            int newwidth = e->globalX() - position.x() - geometry().x();
            QPoint toMove = e->globalPos() - position;
            resize(this->geometry().width() - newwidth, height());
            move(toMove.x(), this->y());
            break;
        }
        case RESIZET: {     //Top
            int newheight = e->globalY() - position.y() - geometry().y();
            QPoint toMove = e->globalPos() - position;
            resize(width(), this->geometry().height() - newheight);
            move(this->x(), toMove.y());
            break;
        }
        case RESIZER: {     //Right
            resize(e->x(), height());
            break;
        }
        case RESIZEBR: {    //Right-Bottom
            resize(e->x(), e->y());
            break;
        }
        }
        this->parentWidget()->repaint();
    }
    emit newGeometry(this->geometry());
}
