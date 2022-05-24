#ifndef CPPBACKEND_H
#define CPPBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

class CppBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int percentage READ percentage NOTIFY percentageChanged)
    Q_PROPERTY(QString time READ time NOTIFY timeChanged)
    Q_PROPERTY(bool waterActive READ waterActive NOTIFY waterActiveChanged)

public:
    explicit CppBackend(QObject *parent = nullptr);

signals:
    void percentageChanged();
    void timeChanged();
    void waterActiveChanged();

private:
    int percentage() const;
    QString time() const;
    bool waterActive() const;
    QTimer m_timer;
    int m_steps = 0;
    int m_direction = 1;
};

#endif // CPPBACKEND_H
