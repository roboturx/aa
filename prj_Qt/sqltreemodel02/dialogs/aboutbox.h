/**************************************************************************
* This file is part of the WebIssues Desktop Client program
* Copyright (C) 2006 Michał Męciński
* Copyright (C) 2007-2017 WebIssues Team
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>
#include <QFrame>
#include <QScrollArea>

class AboutBoxSection;

class QBoxLayout;
class QLabel;
class QToolButton;

class AboutBox : public QDialog
{
    Q_OBJECT
public:
    AboutBox( const QString& title, const QString& message, QWidget* parent );
    ~AboutBox();

public:
    AboutBoxSection* addSection( const QPixmap& pixmap, const QString& message );

private:
    QWidget* m_sectionsWidget;
    QBoxLayout* m_sectionsLayout;
};

class AboutBoxSection : public QFrame
{
    Q_OBJECT
public:
    AboutBoxSection( const QPixmap& pixmap, const QString& message, QWidget* parent );
    ~AboutBoxSection();

protected:
    AboutBoxSection( Qt::WindowFlags flags );

public:
    void setPixmap( const QPixmap& pixmap );
    void setMessage( const QString& message );

    QPushButton* addButton( const QString& text );

    void clearButtons();

private:
    void initialize();

private:
    QBoxLayout* m_mainLayout;
    QBoxLayout* m_buttonsLayout;

    QLabel* m_pixmapLabel;
    QLabel* m_messageLabel;
};

class AboutBoxToolSection : public AboutBoxSection
{
    Q_OBJECT
public:
    AboutBoxToolSection();
    ~AboutBoxToolSection();

public: // overrides
    bool event( QEvent* e );

private slots:
    void updatePosition();

private:
    QToolButton* m_closeButton;
};

class AboutBoxScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    AboutBoxScrollArea( QWidget* parent );
    ~AboutBoxScrollArea();

public: // overrides
    QSize sizeHint() const;
};

#endif
