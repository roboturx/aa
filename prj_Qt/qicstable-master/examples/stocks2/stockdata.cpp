/****************************************************************************
**
** Copyright (C) 2002-2014 Integrated Computer Solutions, Inc.
** All rights reserved.
**
** This file is part of an example program for QicsTable. This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include "stockdata.h"

#include <QFile>
#include <QTextStream>

#include <QicsDataModelDefault.h>

#include <math.h>
#include <stdlib.h>


StockData::StockData(QObject *parent)
    : QObject(parent)
{
    m_gainVector = new GainVector;
    m_dm = new QicsDataModelDefault( 0, 0, this );
}

StockData::~StockData()
{
    m_gainVector->clear();
    delete m_gainVector;
}

void StockData::updateStocks()
{
    m_dm->setEmitSignals(false);

    m_gainVector->clear();

    for (int i = 0; i <= m_dm->lastRow(); ++i)
        updateStock(i);

    emit gainChanged(m_gainVector);

    m_dm->setEmitSignals(true);
}

void StockData::loadDT(const QString &initialFilePath)
{
    QFile f;
    if ( QFile::exists(initialFilePath) )
        f.setFileName(initialFilePath);
    else
        f.setFileName(QString("..\\") + initialFilePath);

    if (!f.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&f);

    m_dm->readASCII(stream);

    f.close();

#ifdef ADD_DATA
    myDM->addColumns(6);
    srand(2332);
    addDay(day_two);
    addDay(day_three);
    QFile out("out.txt");
    out.open(QIODevice::WriteOnly);
    QTextStream outstream(&out);

    myDM->writeASCII(outstream, ';');

    out.close();
#endif
}

void StockData::addDay(int start_col)
{
    for (int i = 0; i < m_dm->numRows(); ++i) {
        float old_price = getFloatValue(i, day_one+cur_idx);
        float new_price = newprice(old_price, (float)0.05, posneg());

        QicsDataFloat fdata(new_price);
        QicsDataFloat high(newprice(new_price, (float)0.05, 1));
        QicsDataFloat low(newprice(new_price, (float)0.05, -1));

        m_dm->setItem(i, start_col+high_idx, high);
        m_dm->setItem(i, start_col+low_idx, low);
        m_dm->setItem(i, start_col+cur_idx, fdata);
    }
}

float StockData::getFloatValue(int row, int col)
{
    const QicsDataItem *itm = m_dm->item(row, col);

    if (itm) {
        if (itm->type() == QicsDataItem_Float)
            return ((QicsDataFloat *) itm)->data();
        else if (itm->type() == QicsDataItem_Double)
            return ((QicsDataDouble *) itm)->data();
        else if (itm->type() == QicsDataItem_Int)
            return ((QicsDataInt *) itm)->data();
    }

    return -1;
}

int StockData::roundf(float f)
{
    int base = (int) floor(f);

    if ((f - base) < 0.5)
        return base;

    return base + 1;
}

float StockData::randf()
{
    return (float) rand() / (float) RAND_MAX;
}

int StockData::posneg()
{
    if (roundf(randf()) < 0.5)
        return -1;

    return 1;
}

float StockData::newprice(float old_price, float percent_change, int updown)
{
    float new_price = old_price + (randf() * percent_change * old_price * updown);
    new_price = ((float) (roundf(new_price * 100))) / 100;

    return new_price;
}

void StockData::updateStock(int row)
{
    float cur_price;

    cur_price = getFloatValue(row, day_zero+cur_idx);
    if (cur_price < 0)
        // yesterday's close
        cur_price = getFloatValue(row, day_one+cur_idx);

    cur_price = newprice(cur_price, (float) 0.02, posneg());
    QicsDataFloat fdata(cur_price);
    updateData(row, day_zero+cur_idx, fdata);

    // Check high
    float high = getFloatValue(row, day_zero+high_idx);
    if ((high < 0) || (cur_price > high))
        updateData(row, day_zero+high_idx, fdata);

    // Check low
    float low = getFloatValue(row, day_zero+low_idx);
    if ((low < 0) || (cur_price < low))
        updateData(row, day_zero+low_idx, fdata);
}

void StockData::updateData(int row, int col, const QicsDataFloat &fd)
{
    // setup model data
    m_dm->setItem(row, col, fd);

    // count stock change
    if (col == day_zero+cur_idx) {
        float yesterday = getFloatValue(row, day_one+cur_idx);
        float today = getFloatValue(row, day_zero+cur_idx);

        // instead of emit signal each time we're changing some value
        // we'll make a vector with pre-calculated row gain
        // and then just update GUI with a single shoot...
        gs _gs = {row, today > yesterday};
        m_gainVector->append( _gs );
    }
}


