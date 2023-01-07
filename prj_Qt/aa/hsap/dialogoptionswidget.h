#ifndef DIALOGOPTIONSWIDGET_H
#define DIALOGOPTIONSWIDGET_H

#include <QGroupBox>
#include "libs/globals.h"


class DialogOptionsWidget : public QGroupBox
{
public:
    explicit DialogOptionsWidget(QWidget *parent = nullptr);

    void addCheckBox(const QString &text, int value);
    void addSpacer();
    int value() const;

private:
    typedef QPair<QCheckBox *, int> CheckBoxEntry;
    QVBoxLayout *layout;
    QList<CheckBoxEntry> checkBoxEntries;
};

#endif // DIALOGOPTIONSWIDGET_H
