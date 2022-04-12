#include "files.h"
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QGridLayout>

Files::Files(QWidget *parent)
    : QMainWindow(parent)
{

    QSplitter *splitter = new QSplitter;
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    setCentralWidget(splitter);

    QTreeView *tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex((model->index(QDir::currentPath())));

    QListView *list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    setWindowTitle("File System");


}

Files::~Files()
{
}

