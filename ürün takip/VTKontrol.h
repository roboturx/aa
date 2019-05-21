#pragma once
#ifndef VTKontrolEt_H
#define VTKontrolEt_H
#include <QObject>
#include <QSqlDatabase>

class VTKontrolEt : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase m_veritaban;
    VTKontrolEt(QObject* parent = 0);
    static VTKontrolEt* createInstance();
public:
    ~VTKontrolEt();
    void SetupDB();
    bool IsOpen();
    bool Connect();
    void Disconnect();
    QString GetError();
    QSqlDatabase GetDB();
    static VTKontrolEt* instance();
};
#endif
