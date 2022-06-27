#include "task.h"
#include "ui_task.h"

Task::Task(QString &name, QWidget *parent) :
    QWidget(parent),
    uit(new Uit::Task)
{
    uit->setupUi(this);
}

Task::~Task()
{
    delete uit;
}

void Task::setName(const QString &name)
{
    uit->checkbox->setText(name);
}

QString Task::name() const
{
    return uit->checkbox->text();
}

bool Task::isCompleed() const
{
    return uit->checkbox->isChecked();
}
