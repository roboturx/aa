#include "main/VTKontrol.h"
#include "main/globals.h"
#include "main/VTTekton.h"


VTKontrolEt::VTKontrolEt(QObject* parent): QObject(parent)
{
}

VTKontrolEt* VTKontrolEt::createInstance()
{
    return new VTKontrolEt();
}

VTKontrolEt::~VTKontrolEt()
= default;

VTKontrolEt* VTKontrolEt::instance()
{
    return Tekton<VTKontrolEt>::instance(VTKontrolEt::createInstance);
}

void VTKontrolEt::SetupDB(){
    m_veritaban = QSqlDatabase::addDatabase("QSQLITE");
    m_veritaban.setDatabaseName(DATABASE_NAME);
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

