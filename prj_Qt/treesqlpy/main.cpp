#include "mainwindow.h"

#include <QApplication>

//void create_sample_data();

int COUNT_PERS_COLS = 3;
//col_persID, col_persLAST_NAME, col_persFIRST_NAME = range(COUNT_PERS_COLS)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




        MainWindow window ;
        window.create_sample_data();
        window.show();

        return a.exec();
}
