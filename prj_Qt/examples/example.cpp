// Example QT code to demonstrate connecting to an ODBC datasource under
// unixODBC. There is deliberately no graphical content in this example
// to keep concentrate on the QODBC code.
// Create a project file example.pro:
//
//SOURCES = example.cpp
//HEADERS =
//TARGET = example
//CONFIG = qt debug
//
// then run qmake -o Makefile example.pro to create a makefile
// then run make to build example program
// NOTE: you need to change the definitions for your DSN below before
// compiling the code
//

#include <iostream.h>
#include <qapplication.h>
#include <qsqldatabase.h>
#include <qobject.h>
#include <qsqlrecord.h>
#include <qsqlquery.h>

#define DB_DRIVER "QODBC3"
// you need to replace the following macros with the values relevant to
// your DSN.
// DB_DBNAME = the name of the DSN you have created in the odbc.ini file
#define DB_DBNAME "demo"
// DB_USER = a username valid for your database
#define DB_USER "demo"
// DB_PASSWD = password for DB_USER
#define DB_PASSWD "easysoft"
// DB_HOST is not relevant to  DSNs
#define DB_HOST ""
// QT will create an ODBC connection string of
// DSN=DB_DBNAME;UID=DB_USER;PWD=DB_PASSWD
int main( int argc, char *argv[] )
{
    QApplication app( argc, argv, FALSE );

    QSqlDatabase *DB = QSqlDatabase::addDatabase( DB_DRIVER );
    if ( DB ) {
        DB->setDatabaseName( DB_DBNAME );
        DB->setUserName( DB_USER );
        DB->setPassword( DB_PASSWD );
        DB->setHostName( DB_HOST );

        if ( DB->open() ) {
	  // Database successfully opened; we can now issue SQL commands.
	  QString table = QString("");
	  // Get a list of tables
	  QStringList list = DB->tables( QSql::Tables);
	  QStringList::Iterator it = list.begin();
	  while( it != list.end() ) {
	    // we save the name of the first table for later
	    if (table.isEmpty()) table = *it;
	    cout << "Table: " << *it << "\n";
	    ++it;
	  }
	  // look at the saved table name to see what fields it has
	  QSqlRecord record = DB->record(table);
	  int fieldcount = record.count();
	  cout << fieldcount << " fields in " << table << "\n";
	  for (int i = 0; i < record.count(); i++) {
	    cout << "Field " << i << " named " << record.fieldName(i) << "\n";
	  }
	  // select from the saved table
          QSqlQuery query(QString("select * from ") + table + QString(" order by account"), DB);
          if (query.isActive()) {
	      int size = query.size();
	      if (query.isSelect())
		cout << "Query is a select\n";
	      // for selects most ODBC drivers return -1 for size
	      // you can't usually use size to determine number of rows
	      cout << "Size in rows of query results is " << size << "\n";
	      cout << "Query executed: " << query.executedQuery() << "\n";

	      while ( query.next() ) {
		cout << "Row: " << query.at() + 1 << ", ";
		//cout << query.value(0).toString();
		for (int i = 0; i < fieldcount; i++) {
		  cout << query.value(i).toString() << ", ";
		}
		cout << "\n";
	      }
            }
	    DB->close();
        } else {
            cout << DB->lastError().text() << "\n";
        }
    }

    return 0;
}
