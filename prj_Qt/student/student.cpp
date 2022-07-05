#include "student.h"

#include <QTextStream>

Student::Student(QString nm, long id, QString major, int year)
    : m_Name(nm), m_Major(major), m_StudeentId(id), m_Year(year)
{

}

QString Student::getClassName() const
{
    return "Student";
}

QString Student::toString() const
{
    QString retval;
    QTextStream os(&retval);
    os <<"Studentclass -*" << getClassName ()
       << "*- name;" << m_Name
       << "     id:" << m_StudeentId
       << "     year:"<< m_Year
       << "     major:"<< m_Major;
    return retval;
}

QString Student::yearStr()
{

}



Undergrad::Undergrad(QString name, long id, QString major, int year, int sat)
    :Student(name, id, major, year ) ,m_SAT(sat)
{

}

QString Undergrad::getClassName() const
{
    return "undergrad "  ;
}

QString Undergrad::toString() const
{
    QString result;
    QTextStream os(&result);
    os << Student::toString ()
       <<"\n SAT:" << m_SAT <<"\n";
    return result;
}



GradStudent::GradStudent(QString nm, long id, QString major, int yr, Support support)
    :Student (nm, id, major, yr) , m_support(support)
{

}

QString GradStudent::getClassName() const
{
    return "gradstd";
}

QString GradStudent::toString() const
{
    return QString("%1%2%3 \n")
        .arg(Student::toString ())
        .arg("\n SUPPRT: ")
        .arg(supportStr (m_support));
}
