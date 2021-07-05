#ifndef LOGGER_H
#define LOGGER_H


// https://github.com/KubaO/stackoverflown/tree/master/questions/qdebug-window-output-52061269
#include <QtWidgets>

struct LogToModelData {
    bool installed;
    QtMessageHandler previous = {};
    QList<QPointer<QObject>> models;
};

Q_GLOBAL_STATIC(LogToModelData, logToModelData)

void logToModelHandler(QtMsgType type,
                       const QMessageLogContext &context,
                       const QString &msg) ;

void logToModel(QObject *model) ;

void rescrollToBottom(QAbstractScrollArea *view);

#endif // LOGGER_H
