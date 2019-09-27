#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class DragWidget;
class CustomButton;
QT_END_NAMESPACE

//! [0]
class DragWidget : public QWidget
{
public:
    explicit DragWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;


};
//! [0]
//!
//!



class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = nullptr) ;
    ~CustomButton() override;

public:
    QString No;
    QLabel* resim;
    QLabel* ieno;
    QLabel* kurumno;
    QPixmap* pixmap;
    QImage SimileIcon;
    bool IsBkColorEnabled;
    QColor Bkclor;


    int getObjNo() const;
    void setObjNo(int value);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int objNo;

private slots:
    void smSLOT();

};

#endif
