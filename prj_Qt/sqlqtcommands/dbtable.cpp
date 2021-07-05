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

bool DBTable::createTable(QString createStr)
{
    QSqlQuery query;
    query.prepare(createStr);
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return false ;
    }
    else
    {
        qDebug("Table created!");
        return true;
    }
}

bool DBTable::insertTable(QString createStr)
{
    QSqlQuery query;
    query.prepare(createStr);
    if( !query.exec() )
    {
        if ( query.lastError().text().contains("UNIQUE", Qt::CaseInsensitive)  )
            qDebug("Record already there");
        else
            qDebug() << query.lastError().text();
        return false ;
    }
    else
    {
        qDebug("Record inserted!");
        return true;
    }
}

bool DBTable::listTable(QString createStr, QString spec)
{
    QSqlQuery query;
    query.prepare(createStr);
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return false ;
    }
    else
    {
        qDebug( ) <<spec + " Table Listed!";
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
