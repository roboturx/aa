#ifndef ARAYUZ_H
#define ARAYUZ_H

#include "globals.h"

namespace Ui {
class Arayuz;
}

class Arayuz : public QWidget
{
    Q_OBJECT

public:
    explicit Arayuz(QWidget *parent = nullptr);
    ~Arayuz();

    Dbase * dbase;
private:
    Ui::Arayuz *ui;
};

#endif // ARAYUZ_H
