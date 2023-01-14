#include "cw_dlg_options.h"

cw_Dlg_Options::cw_Dlg_Options(QWidget *parent) :
    QGroupBox(parent) , layout(new QVBoxLayout)
{
    setTitle("Options");
    setLayout(layout);
}

void cw_Dlg_Options::addCheckBox(const QString &text, int value)
{
    QCheckBox *checkBox = new QCheckBox(text);
    layout->addWidget(checkBox);
    checkBoxEntries.append(CheckBoxEntry(checkBox, value));
}

void cw_Dlg_Options::addSpacer()
{
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
}

int cw_Dlg_Options::value() const
{
    int result = 0;
    for (const CheckBoxEntry &checkboxEntry : std::as_const(checkBoxEntries)) {
        if (checkboxEntry.first->isChecked())
            result |= checkboxEntry.second;
    }
    return result;
}
