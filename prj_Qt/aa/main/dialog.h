// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef DIALOG_H
#define DIALOG_H

#include "libs/globals.h"
#include "main/dialogoptionswidget.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QErrorMessage;
QT_END_NAMESPACE






class Dialog : public QWidget
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);

   // QColor getcolor() { return m_color; };

public slots:
    void setColor();

private slots:
    void setInteger();
    void setDouble();
    void setItem();
    void setText();
    void setMultiLineText();
    void setFont();
    void setExistingDirectory();
    void setOpenFileName();
    void setOpenFileNames();
    void setSaveFileName();
    void criticalMessage();
    void informationMessage();
    void questionMessage();
    void warningMessage();
    void errorMessage();

private:
 //   QColor m_color;
    QLabel *integerLabel;
    QLabel *doubleLabel;
    QLabel *itemLabel;
    QLabel *textLabel;
    QLabel *multiLineTextLabel;
    QLabel *colorLabel;
    QLabel *fontLabel;
    QLabel *directoryLabel;
    QLabel *openFileNameLabel;
    QLabel *openFileNamesLabel;
    QLabel *saveFileNameLabel;
    QLabel *criticalLabel;
    QLabel *informationLabel;
    QLabel *questionLabel;
    QLabel *warningLabel;
    QLabel *errorLabel;
    QErrorMessage *errorMessageDialog;
    DialogOptionsWidget *fileDialogOptionsWidget;
    DialogOptionsWidget *colorDialogOptionsWidget;
    DialogOptionsWidget *fontDialogOptionsWidget;
    QString openFilesPath;
};

#endif
