/*
    Copyright (c) 2009-10 Qtrac Ltd. All rights reserved.

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include "linkfetcher.hpp"
#include <QFile>
#include <QWebEngineFrame>


LinkFetcher::LinkFetcher(const QString &site_,
        const QString &scriptOrScriptName_, QObject *parent)
    : QObject(parent), site(site_),
      scriptOrScriptName(scriptOrScriptName_)
{
    QWebEngineSettings *webSettings = page.settings();
    webSettings->setAttribute(QWebEngineSettings::AutoLoadImages, false);
    webSettings->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    webSettings->setAttribute(QWebEngineSettings::JavaEnabled, false);
    webSettings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    webSettings->setAttribute(QWebEngineSettings::PrivateBrowsingEnabled,
                              true);

    connect(page.mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(injectJavaScriptIntoWindowObject()));
    connect(&page, SIGNAL(loadFinished(bool)),
            this, SLOT(fetchLinks(bool)));
}


void LinkFetcher::injectJavaScriptIntoWindowObject()
{
    page.mainFrame()->addToJavaScriptWindowObject("linkFetcher",
                                                  this);
}


void LinkFetcher::load(const QString &url)
{
    clear();
    page.mainFrame()->load(QUrl(url));
}


void LinkFetcher::fetchLinks(bool ok)
{
    if (!ok) {
        emit finished(false);
        return;
    }
    QString javaScript = scriptOrScriptName;
    if (scriptOrScriptName.endsWith(".js")) {
        QFile file(scriptOrScriptName);
        if (!file.open(QIODevice::ReadOnly)) {
            emit finished(false);
            return;
        }
        javaScript = QString::fromUtf8(file.readAll());
    }
    QWebEngineFrame *frame = page.mainFrame();
    frame->evaluateJavaScript(javaScript);
    emit finished(true);
}


void LinkFetcher::addUrlAndName(const QString &url,
                                const QString &name)
{
    if (url.startsWith("http://"))
        m_namesForUrls[url] = name;
    else
        m_namesForUrls[site + url] = name;
}
