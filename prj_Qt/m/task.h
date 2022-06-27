#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Uit {  class Task;   }
QT_END_NAMESPACE

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(QString &name, QWidget *parent = 0);
    ~Task();

    void setName(const QString &name);
    QString name() const;
    bool isCompleed() const;

private:
    Uit::Task *uit;
};

#endif // TASK_H
