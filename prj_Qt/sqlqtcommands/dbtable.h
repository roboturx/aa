#ifndef DBTable_H
#define DBTable_H

#include <QObject>
#include <QSqlQuery>

class DBTable : public QObject
{
    Q_OBJECT

public:
    DBTable(QObject* parent , QString tableName);

    QString setQuery(QString queryStr);
    bool createTable(QList<QString> fields);
    bool recInsert(QVariant fields);
    int rec();

private:
    QString m_queryStr{};
    int m_DBTable;
    QString m_tableName;

};

#endif // DBTable_H
