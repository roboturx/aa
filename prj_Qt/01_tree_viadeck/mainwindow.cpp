/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "treemodel.h"
#include "treesqlmodel.h"
#include "viadecksqlmodel.h"

#include <QFile>
#include <QSqlQuery>
#include <QTreeView>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    const QStringList headers01({tr("Title"), tr("Description")});

    /// view01
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *modelTXT = new TreeModel(headers01, file.readAll(), this);
    file.close();

    view01->setModel(modelTXT);
    for (int column = 0; column < modelTXT->columnCount(); ++column)
        view01->resizeColumnToContents(column);


    /// view02
    ///

  //  QSqlQuery q;
   // const QStringList headers02({tr("ID Mosel"), tr("SQL AccCode"), tr("GrpCode")});

    TreeSqlModel *modelSQL = new TreeSqlModel(this);
    view02->setModel(modelSQL);
    for (int column = 0; column < modelSQL->columnCount(); ++column)
        view02->resizeColumnToContents(column);
    view02->expandAll();

    ///// view 03
    ///
    ///
    ///  vladeck - qt forum


    QList<int> group_column_indexes;

    /// group by column 0...
    /// can be any combination of column indexes
    group_column_indexes <<0;
    QSqlQuery  query("SELECT * FROM dbtb_accounts "
                     "ORDER BY f_AccountCode ASC ");


    test::itemdata::ViadeckSqlModel* model03 = new test::itemdata
                                        ::ViadeckSqlModel();
    // SELECT ... statement, for example
    model03->SetQuery(query);
    model03->SetGroupByIndexes(group_column_indexes);
    /// Note, that you must format this using same
    /// indexes for grouping...
    /// if we choose to hide columns 0, 3 & 4,
    /// then the code/format
    /// would be something like:
    ///
    /// group_column_indexes << 0 << 3 << 4
    /// ...
    /// model->SetGroupTitleFormat("Group {0} is
    /// grouped with {3} and {4}");
    model03->SetGroupTitleFormat("Group {0}");
    model03->Select();

    //QTreeView *_TrvPackages = new QTreeView;
    view03->setAllColumnsShowFocus(true);
    view03->setModel(model03);

    for (int i = 0; i < view03->model()->rowCount(); ++i)
        view03->setFirstColumnSpanned(i, QModelIndex(), true);

    view03->expandAll();
    //    QTreeView *_TrvPackages = new QTreeView;
    //        _TrvPackages->setAllColumnsShowFocus(false);
    //        _TrvPackages->setModel(model);

    //        for (int i = 0; i < _TrvPackages->model()->rowCount(); ++i)
    //            _TrvPackages->setFirstColumnSpanned(i, QModelIndex(), true);

    //        _TrvPackages->expandAll();



    ////
    ///
    ///
    ///
    ///

    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    connect(view02->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::updateActions);




    connect(actionsMenu, &QMenu::aboutToShow, this, &MainWindow::updateActions);
    connect(insertRowAction, &QAction::triggered, this, &MainWindow::insertRow);
    connect(insertColumnAction, &QAction::triggered, this, &MainWindow::insertColumn);
    connect(removeRowAction, &QAction::triggered, this, &MainWindow::removeRow);
    connect(removeColumnAction, &QAction::triggered, this, &MainWindow::removeColumn);
    connect(insertChildAction, &QAction::triggered, this, &MainWindow::insertChild);

    updateActions();
}

void MainWindow::insertChild()
{
    const QModelIndex index = view02->selectionModel()->currentIndex();
    QAbstractItemModel *model = view02->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No itemdata]")), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
    }

    view02->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                              QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool MainWindow::insertColumn()
{
    QAbstractItemModel *model = view02->model();
    int column = view02->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    updateActions();

    return changed;
}

void MainWindow::insertRow()
{
    const QModelIndex index = view02->selectionModel()->currentIndex();
    QAbstractItemModel *model = view02->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        const QModelIndex child = model->index(index.row() + 1, column, index.parent());
        model->setData(child, QVariant(tr("[No itemdata]")), Qt::EditRole);
    }
}

bool MainWindow::removeColumn()
{
    QAbstractItemModel *model = view02->model();
    const int column = view02->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    const bool changed = model->removeColumn(column);
    if (changed)
        updateActions();

    return changed;
}

void MainWindow::removeRow()
{
    const QModelIndex index = view02->selectionModel()->currentIndex();
    QAbstractItemModel *model = view02->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
    const bool hasSelection = !view02->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    const bool hasCurrent = view02->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        view02->closePersistentEditor(view02->selectionModel()->currentIndex());

        const int row = view02->selectionModel()->currentIndex().row();
        const int column = view02->selectionModel()->currentIndex().column();
        if (view02->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}
