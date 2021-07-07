#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql>
#include <QtGui>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void populateDataItem();

public slots:
    void addnew();
    void remove();
    void save();


private:
    Ui::Widget *ui;
    QSqlTableModel *model;
    QSqlDatabase db;
    bool initDatabase();
    void closeDatabase();

};
#endif // WIDGET_H

