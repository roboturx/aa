#include "mainwindow.h"
#include "dbtable.h"
#include <QApplication>

#include <QtSql>
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    DBTable namesTable (this,"names");

    namesTable.createTable( "CREATE TABLE IF NOT EXISTS names "
                           "(id INTEGER UNIQUE PRIMARY KEY, "
                           "firstname TEXT, "
                           "lastname TEXT)" );

    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (1, 'John', 'Doe')" );
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (2, 'Jane', 'Doe')" );
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (3, 'James', 'Doe')");
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (4, 'Judy', 'Doe')");
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (5, 'Richard', 'Roe')");
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (6, 'Jane', 'Roe')");
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (7, 'John', 'Noakes')");
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (8, 'Donna', 'Doe')");
    namesTable.insertTable("INSERT INTO names (id, firstname, lastname) VALUES (9, 'Ralph', 'Roe')");
    QSqlQuery qry;

    qDebug("-------------------------------------- select list");
    qDebug("SELECT * FROM names");
    qry.prepare( "SELECT * FROM names" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
    {
        qDebug( "Selected!" );

        QSqlRecord rec = qry.record();

        int cols = rec.count();

        for( int c=0; c<cols; c++ )
            qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

        for( int r=0; qry.next(); r++ )
            for( int c=0; c<cols; c++ )
                qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
    }



    //qDebug( ) <<  namesTable.recCount() ;


    qDebug("-------------------------------------- select list where");
    qDebug("SELECT firstname, lastname FROM names WHERE lastname = 'Roe'");
    qry.prepare( "SELECT firstname, lastname FROM names WHERE lastname = 'Roe'" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
    {
        qDebug( "Selected!" );

        QSqlRecord rec = qry.record();

        int cols = rec.count();

        for( int c=0; c<cols; c++ )
            qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

        for( int r=0; qry.next(); r++ )
            for( int c=0; c<cols; c++ )
                qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
    }


    qDebug("-------------------------------------- select and list where orde");
    qDebug("SELECT firstname, lastname FROM names "
           "WHERE lastname = 'Roe' ORDER BY firstname");
    qry.prepare( "SELECT firstname, lastname FROM names WHERE lastname = 'Roe' ORDER BY firstname" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
    {
        qDebug( "Selected!" );

        QSqlRecord rec = qry.record();

        int cols = rec.count();

        for( int c=0; c<cols; c++ )
            qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

        for( int r=0; qry.next(); r++ )
            for( int c=0; c<cols; c++ )
                qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
    }


    qDebug("-------------------------------------- select and list group");
    qDebug("SELECT lastname, COUNT(*) as 'members' FROM names "
           "GROUP BY lastname ORDER BY lastname");
    qry.prepare( "SELECT lastname, COUNT(*) as 'members' FROM names GROUP BY lastname ORDER BY lastname" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
    {
        qDebug( "Selected!" );

        QSqlRecord rec = qry.record();

        int cols = rec.count();

        for( int c=0; c<cols; c++ )
            qDebug() << QString( "Column %1: %2" ).arg( c )
                            .arg( rec.fieldName(c) );

        for( int r=0; qry.next(); r++ )
            for( int c=0; c<cols; c++ )
                qDebug() << QString( "Row %1, %2: %3" ).arg( r )
                                .arg( rec.fieldName(c) )
                                .arg( qry.value(c).toString() );
    }

    qDebug("-------------------------------------- update");
    qDebug("UPDATE names SET firstname = 'Nisse', lastname = 'Svensson' WHERE id = 7");
    qry.prepare( "UPDATE names SET firstname = 'Nisse', lastname = 'Svensson' WHERE id = 7" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Updated!" );

    qry.prepare( "UPDATE names SET lastname = 'Johnson' WHERE firstname = 'Jane'" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Updated!" );

    //        RecCount recCount(this,  "names");

    //qDebug( ) <<  namesTable.recCount() ;


    qDebug("-------------------------------------- delete");
    qDebug("DELETE FROM names WHERE id = 7");
    qry.prepare( "DELETE FROM names WHERE id = 7" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Deleted!" );

    qry.prepare( "DELETE FROM names WHERE lastname = 'Johnson'" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Deleted!" );



    //qDebug( ) <<  namesTable.recCount() ;

    //  db.close();

    //return 0;


}

MainWindow::~MainWindow()
{
}

