/****************************************************************************
**
** Copyright (C) 2002-2020 Integrated Computer Solutions, Inc.
** All rights reserved.
**
** This file is part of an example program for QicsTable. This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/
#include "doubleTable.h"

#include <QApplication>
#include <QMenuBar>
#include <QTimer>
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
#include <QRandomGenerator>
#endif
#include <QicsColumnHeader.h>
#include <QicsCell.h>
#include <QicsRowHeader.h>
#include <QicsTable.h>
#include <QicsDataModelDefault.h>


// DoubleTable class:
DoubleTable::DoubleTable(QWidget* parent, QicsDataModelDefault* dataModel, const QString& caption)
    : QMainWindow(parent)
{
    setWindowTitle(caption);
    m_table = new QicsTable(dataModel, this);
    setCentralWidget(m_table);
    m_table->setVisibleRows(COUNT_ROWS);
    m_table->setVisibleColumns(COUNT_COLS);
    QString textCell;

    for (int i = 0; i < COUNT_ROWS; ++i)
        for (int j = 0; j < COUNT_COLS; ++j) {
            m_table->columnHeaderRef().cellRef(0, j).setLabel(textCell.setNum(j));
            m_table->rowHeaderRef().cellRef(i, 0).setLabel(textCell.setNum(i));
            textCell = QString("Cell (");
            textCell += m_table->columnHeaderRef().cellRef(0, j).label();
            textCell += QString(";");
            textCell += QString((m_table->rowHeaderRef().cellRef(i, 0).label()));
            textCell += QString(")");
            dataModel->setItem(i, j, QicsDataString(textCell));
            m_table->cellRef(i, j).setWidthInChars(7);
        }
}

DoubleTable::~DoubleTable()
{
}

// Tester class:
Tester::Tester(DoubleTable* table1, DoubleTable* table2, QicsDataModel* dataModel)
{
    table1 = table1;
    table2 = table2;
    m_dataModel = dataModel;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(changeItems()));
    m_timer->start(1000);
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
    qsrand(QDateTime::currentDateTime().toTime_t());
#endif
}

Tester::~Tester()
{
}

void Tester::changeItems()
{
    int length;
    QString str;
    char letter;

    for (int i = 0; i < COUNT_ROWS; ++i)
        for (int j = 0; j < COUNT_COLS; ++j) {
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
            switch (qrand() % 3 + 1)
#else
            switch (QRandomGenerator::global()->generate() % 3 + 1)
#endif
            {
            case 2:
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
                m_dataModel->setItem(i, j, QicsDataFloat(static_cast <float> (qrand() % 100) / ((rand() % 10) + 3.0f)));
#else
                m_dataModel->setItem(i, j, QicsDataFloat(static_cast <float> (QRandomGenerator::global()->generate() % 100) / ((rand() % 10) + 3.0f)));
#endif
                break;
            case 3:
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
                length = qrand() % 7 + 1;
#else
                length = QRandomGenerator::global()->generate() % 7 + 1;
#endif
                for (int k = 0; k < length; ++k) {
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
                    letter = qrand() % 25 + 65;
#else
                    letter = QRandomGenerator::global()->generate() % 25 + 65;
#endif
                    str += QString(letter);
                }
                m_dataModel->setItem(i, j, QicsDataString(str));
                str = QString();
                break;
            default:
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
                m_dataModel->setItem(i, j, QicsDataInt(qrand() % 100));
#else
                m_dataModel->setItem(i, j, QicsDataInt(QRandomGenerator::global()->generate() % 100));
#endif
                break;
            }
        }
}
