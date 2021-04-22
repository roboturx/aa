/****************************************************************************
* Simple template-based relational database
* Copyright (C) 2006-2010 Michał Męciński
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*   3. Neither the name of the copyright holder nor the names of the
*      contributors may be used to endorse or promote products derived from
*      this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/

#include "editdialog.h"

#include <QPushButton>

EditDialog::EditDialog( QWidget* parent ) : QDialog( parent )
{
    setupUi( );

    buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
}

EditDialog::~EditDialog()
{
}

void EditDialog::setName( const QString& name )
{
   nameEdit->setText( name );
}

QString EditDialog::name() const
{
    return nameEdit->text();
}

void EditDialog::setAddressEnabled( bool enabled )
{
    addressEdit->setEnabled( enabled );
}

void EditDialog::setAddress( const QString& address )
{
    addressEdit->setText( address );
}

QString EditDialog::address() const
{
    return addressEdit->text();
}

void EditDialog::setPhoneEnabled( bool enabled )
{
    phoneEdit->setEnabled( enabled );
}

void EditDialog::setPhone( const QString& phone )
{
    phoneEdit->setText( phone );
}

QString EditDialog::phone() const
{
    return phoneEdit->text();
}

void EditDialog::on_nameEdit_textChanged( const QString& name )
{
    buttonBox->button( QDialogButtonBox::Ok )->setEnabled( !name.isEmpty() );
}


void EditDialog::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("EditDialog"));
    resize(287, 137);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    nameEdit = new QLineEdit(this);
    nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

    gridLayout->addWidget(nameEdit, 0, 1, 1, 1);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout->addWidget(label_3, 2, 0, 1, 1);

    phoneEdit = new QLineEdit(this);
    phoneEdit->setObjectName(QString::fromUtf8("phoneEdit"));

    gridLayout->addWidget(phoneEdit, 2, 1, 1, 1);

    addressEdit = new QLineEdit(this);
    addressEdit->setObjectName(QString::fromUtf8("addressEdit"));

    gridLayout->addWidget(addressEdit, 1, 1, 1, 1);


    verticalLayout->addLayout(gridLayout);

    verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout->addWidget(buttonBox);

#if QT_CONFIG(shortcut)
    label->setBuddy(nameEdit);
    label_2->setBuddy(addressEdit);
    label_3->setBuddy(phoneEdit);
#endif // QT_CONFIG(shortcut)
    QWidget::setTabOrder(nameEdit, addressEdit);
    QWidget::setTabOrder(addressEdit, phoneEdit);
    QWidget::setTabOrder(phoneEdit, buttonBox);

    retranslateUi(this);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, qOverload<>(&QDialog::accept));
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, qOverload<>(&QDialog::reject));

    QMetaObject::connectSlotsByName(this);
} // setupUi

void EditDialog::retranslateUi(QDialog *EditDialog)
{
    EditDialog->setWindowTitle(QCoreApplication::translate("EditDialog", "Edit", nullptr));
    label->setText(QCoreApplication::translate("EditDialog", "&Name:", nullptr));
    label_2->setText(QCoreApplication::translate("EditDialog", "&Address:", nullptr));
    label_3->setText(QCoreApplication::translate("EditDialog", "&Phone:", nullptr));
} // retranslateUi
