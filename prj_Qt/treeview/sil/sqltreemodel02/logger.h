#ifndef LOGGER_H
#define LOGGER_H


// https://github.com/KubaO/stackoverflown/tree/master/questions/qdebug-window-output-52061269


#include <QAbstractScrollArea>
#include <QObject>
#include <QtWidgets>

struct LogToModelData {
    bool installed;
    QtMessageHandler previous = {};
    QList<QPointer<QObject>> models;
};
Q_GLOBAL_STATIC(LogToModelData, logToModelData)

class Logger : public QWidget
{
    Q_OBJECT
public:
    explicit Logger(QWidget *parent = nullptr);

    QListView *view ;
    QTextBrowser* browser;


    void logToModelHandler(QtMsgType type,
                           const QMessageLogContext &context,
                           const QString &msg) ;

    void logToModel(QObject *model) ;

    void rescrollToBottom(QAbstractScrollArea *view);

signals:

};

#endif // LOGGER_H
