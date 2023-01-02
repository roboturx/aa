#ifndef MyClass_H
#define MyClass_H

#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass(const QString &text,
            QObject *parent = nullptr);
    ~MyClass();

    const QString &text() const;
    int getLengthOfText() const;

public slots:
    void setText(const QString &text) ;

signals:
    void textChanged(const QString &);

private:
    QString m_text;

};
#endif // MyClass_H
