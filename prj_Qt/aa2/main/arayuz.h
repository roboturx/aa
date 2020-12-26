#ifndef ARAYUZ_H
#define ARAYUZ_H

#include "globals.h"
#include "dbase.h"
namespace Ui {
class Arayuz;
}

class Arayuz : public QWidget
{
    Q_OBJECT

public:
    explicit Arayuz(QWidget *parent = nullptr);
    ~Arayuz();

   DBase* dbase;
private:
    Ui::Arayuz *ui;
};

#endif // ARAYUZ_H
