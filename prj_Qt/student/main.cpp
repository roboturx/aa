#include <QCoreApplication>

#include "student.h"
#include <QTextStream>



static QTextStream cout (stdout);

void finish(Student* student)
{
    cout << "\n The followind "
         << student->getClassName ()
         << "has applied for graduation\n"
         << student->toString () <<"\n";
}

int main()
{
    //QCoreApplication a(argc, argv);

    Undergrad us("Ali Umt Balcı", 2222, "arch", 4, 1220);
    GradStudent gs("murat", 1111, "conmp", 3, GradStudent::fellowship );

    cout <<"DATAS\n";
    cout << gs.toString () << Qt::endl  ;
    cout << us.toString () <<Qt::endl ;
    cout << "atfinish";
    finish (&us);
    finish (&gs);

    return 0;
}
