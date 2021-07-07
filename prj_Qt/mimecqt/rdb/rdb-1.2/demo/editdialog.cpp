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
    m_ui.setupUi( this );

    m_ui.buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
}

EditDialog::~EditDialog()
{
}

void EditDialog::setName( const QString& name )
{
    m_ui.nameEdit->setText( name );
}

QString EditDialog::name() const
{
    return m_ui.nameEdit->text();
}

void EditDialog::setAddressEnabled( bool enabled )
{
    m_ui.addressEdit->setEnabled( enabled );
}

void EditDialog::setAddress( const QString& address )
{
    m_ui.addressEdit->setText( address );
}

QString EditDialog::address() const
{
    return m_ui.addressEdit->text();
}

void EditDialog::setPhoneEnabled( bool enabled )
{
    m_ui.phoneEdit->setEnabled( enabled );
}

void EditDialog::setPhone( const QString& phone )
{
    m_ui.phoneEdit->setText( phone );
}

QString EditDialog::phone() const
{
    return m_ui.phoneEdit->text();
}

void EditDialog::on_nameEdit_textChanged( const QString& name )
{
    m_ui.buttonBox->button( QDialogButtonBox::Ok )->setEnabled( !name.isEmpty() );
}
