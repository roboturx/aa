#ifndef MAINWINDOWXXXX_H
#define MAINWINDOWXXXX_H

#include <QMainWindow>

namespace Ui {
class MainWindowxxxx;
}

class MainWindowxxxx : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowxxxx(QWidget *parent = nullptr);
    ~MainWindowxxxx();

private:
    Ui::MainWindowxxxx *ui;
};

#endif // MAINWINDOWXXXX_H
