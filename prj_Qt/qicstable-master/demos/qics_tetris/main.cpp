/****************************************************************************
**
** Copyright (C) 2002-2014 Integrated Computer Solutions, Inc.
** All rights reserved.
**
** This file is part of an example program for QicsTable. This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include <QApplication>

#include "tetris.h"


int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    QicsTetris* tetris = new QicsTetris();
    tetris->setFixedSize(350, 535);
    tetris->show();
    return app.exec();
}


