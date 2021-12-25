#ifndef EDITDIALOG_H

#include <QDialog>
#include "QtWidgets"

//#include "ui_editdialog.h"

class EditDialog : public QDialog
{
    Q_OBJECT
public:
    EditDialog( QWidget* parent );
    ~EditDialog();

public:
    void setName( const QString& name );
    QString name() const;

    void setAddressEnabled( bool enabled );

    void setAddress( const QString& address );
    QString address() const;

    void setPhoneEnabled( bool enabled );

    void setPhone( const QString& phone );
    QString phone() const;

private slots:
    void on_nameEdit_textChanged( const QString& name );

private:
  //  Ui::EditDialog* m_ui;

public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *phoneEdit;
    QLineEdit *addressEdit;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi();
    void retranslateUi(QDialog *EditDialog);


};

#endif
