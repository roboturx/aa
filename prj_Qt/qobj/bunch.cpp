#include <QTextStream>
#include <QDebug>
#include "person.h"
#include <QDebug>

static QTextStream cout(stdout);
void growBunch() ;
//start


int main(int , char**) {
    qDebug() << "-111-------main ";
   growBunch();
   cout << "-222-------We have now returned from growBunch()."
        <<  "\nWhat happened to Alice?" << Qt::endl;
   return 0;
}


void growBunch() {
    qDebug() << "01 First we create a bunch of objects. bunch qobject created - " << Qt::endl;
    QObject bunch;
    bunch.setObjectName("A Stack Object");
    bunch.dumpObjectInfo ();
        /* A local stack object - not a pointer */
    /* other objects are created on the heap */
    qDebug() << "02 person* mike creating...";
    Person* mike = new Person("Mike", &bunch);
    qDebug() << "03 person* mike created.";
    Person* carol = new Person("Carol", &bunch);
    qDebug() << "04 person* carol created.";
    new Person("Greg", mike);
    /* We do not need
       to keep pointers to children, because we can
       reach them via object navigation. */
    new Person("Peter", mike);
    new Person("Bobby", mike);
    new Person("Marcia", carol);
    new Person("Jan", carol);
    new Person("Cindy", carol);
    new Person("Alice");
    bunch.dumpObjectInfo ();
  //  bunch.
    /* Alice has no parent - memory leak? */
        qDebug() << "\n05 Display the list using "
           "QObject::dumpObjectTree()"
             << Qt::endl;
    bunch.dumpObjectTree();
    /* dumpObjectTree() output will appear on the
       screen only if the Qt library has been
        compiled with the debugging option turned on.*/
    cout << "\n06 Ready to return from growBunch() -"
         << " Destroy all local stack objects." << Qt::endl;
}


//end
