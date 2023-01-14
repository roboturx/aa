#ifndef cw_Dlg_Options_H
#define cw_Dlg_Options_H

#include <QGroupBox>
#include "libs/globals.h"


class cw_Dlg_Options : public QGroupBox
{
public:
    explicit cw_Dlg_Options(QWidget *parent = nullptr);

    void addCheckBox(const QString &text, int value);
    void addSpacer();
    int value() const;

private:
    typedef QPair<QCheckBox *, int> CheckBoxEntry;
    QVBoxLayout *layout;
    QList<CheckBoxEntry> checkBoxEntries;
};

#endif // cw_Dlg_Options_H
