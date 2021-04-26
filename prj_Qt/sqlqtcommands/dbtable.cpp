#include <QSqlError>
#include <QSqlQuery>

#include "dbtable.h"

DBTable::DBTable(QObject* parent, QString tableName)
{
    m_tableName = tableName;

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./testdatabase.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }
    qDebug("-------------------------------------- connect");
    qDebug( "Connected!" );
    qDebug("--------------------------------------");


    rec();
}

QString DBTable::setQuery(QString queryStr)
{
    m_queryStr = queryStr;


}

bool DBTable::createTable(QList<QString> fields)
{
    QSqlQuery query;

    int fieldsCount = QString::number(fields.at(0));
    for (int i=0 ; fieldsCount ; i++)
    {

    }

    QListIterator<float> i(fields);
    while (fields.hasNext())
        qDebug() << fields.next();


    query.prepare(fields);
    if( !query.exec() )
    {
        qDebug(query.lastError().text());
        return false ;
    }
    else
    {
        qDebug("Table created!");
        return true;
    }
}

int DBTable::rec()
{

    QSqlQuery query;
    m_DBTable =-1;
    int DBTable = 0;
    query.prepare ("SELECT * FROM " + m_tableName );
    if( query.exec ()){
        while( query.next() )
        {
            DBTable ++;
        }
        m_DBTable = DBTable;
    }
    return m_DBTable;
}
