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
