
#include "connection.h"
#include "customsqlmodel.h"
#include "editablesqlmodel.h"

#include <QApplication>
#include <QTableView>

#include <stdlib.h>

#include "dbase.h"


void initializeModel(QSqlQueryModel *model)
{
    model->setQuery("select * from person");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));


}

QTableView* createView(QSqlQueryModel *model, const QString &title = "")
{
    QTableView *view = new QTableView;
    view->setModel(model);
    static int offset = 100;

    view->setWindowTitle(title);
    view->move(100 + offset, 100 + offset);
    offset += 20;
    view->show();

    return view;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    if (!createConnection())
//        return EXIT_FAILURE;
    dBase db;
    db.openDb();

    EditableSqlModel editableModel;
    initializeModel(&editableModel);
    createView(&editableModel, QObject::tr("Editable Query Model -------------"));

    return app.exec();
}
