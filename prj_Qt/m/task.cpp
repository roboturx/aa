#include "task.h"
#include "ui_task.h"

Task::Task(QString &name, QWidget *parent) :
    QWidget(parent),
    uitt(new Uit::Task)
{
    uitt->setupUi(this);
}

Task::~Task()
{
    delete uitt;
}

void Task::setName(const QString &name)
{
    uitt->checkbox->setText(name);
}

QString Task::name() const
{
    return uitt ->checkbox->text();
}

bool Task::isCompleed() const
{
    return uitt->checkbox->isChecked();
}
