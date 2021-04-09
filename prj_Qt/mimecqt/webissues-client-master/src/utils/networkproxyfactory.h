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

#ifndef NETWORKPROXYFACTORY_H
#define NETWORKPROXYFACTORY_H

#include <QNetworkProxyFactory>

class NetworkProxyFactory : public QNetworkProxyFactory
{
public:
    NetworkProxyFactory();
    ~NetworkProxyFactory();

public: // overrides
    QList<QNetworkProxy> queryProxy( const QNetworkProxyQuery& query );
};

#endif
