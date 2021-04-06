#include "VTKontrol.h"
#include <QObject>
#include "VTTekton.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

VTKontrolEt::VTKontrolEt(QObject* parent): QObject(parent)
{
     qDebug() << "4 03 vtkontrol et";
}

VTKontrolEt* VTKontrolEt::createInstance()
{
    qDebug() << "4 02 create instance ";
    return new VTKontrolEt();
}

VTKontrolEt::~VTKontrolEt()
{
}

VTKontrolEt* VTKontrolEt::instance()
{
     qDebug() << "4 01 instance ";
    return Tekton<VTKontrolEt>::instance(VTKontrolEt::createInstance);
}

void VTKontrolEt::SetupDB(){
     qDebug() << "2221";
    m_veritaban = QSqlDatabase::addDatabase("QSQLITE");
    m_veritaban.setDatabaseName("dbprdct");
     qDebug() << "2222";
}

bool VTKontrolEt::IsOpen(){
    return m_veritaban.isOpen();
}

bool VTKontrolEt::Connect(){
    return m_veritaban.open();
}

void VTKontrolEt::Disconnect(){
    m_veritaban.close();
}

QString VTKontrolEt::GetError(){
    return m_veritaban.lastError().text();
}

QSqlDatabase VTKontrolEt::GetDB(){
    return m_veritaban;
}
