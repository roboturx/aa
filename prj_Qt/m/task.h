#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QString>

namespace Ui_checkbox {  class Task;   }


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
    Ui_checkbox::Task *uitt;
};

#endif // TASK_H
