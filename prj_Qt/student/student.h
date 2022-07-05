#ifndef STUDENT_H
#define STUDENT_H


#include <QString>

class Student
{
public:
    Student (QString nm, long id, QString major, int year = 1 );
    ~Student() {}
    QString getClassName() const;
    QString toString() const;
private:
    QString m_Name;
    QString m_Major;
    long m_StudeentId;

protected:
    int m_Year;
    QString yearStr();
};

class Undergrad : public Student
{
public:
    Undergrad (QString name, long id, QString major, int year, int sat);
    QString getClassName() const;
    QString toString() const;
private:
    int m_SAT;
};

class GradStudent : public Student
{
public:
    enum Support {ta, ra, fellowship, other};
    GradStudent (QString nnm, long id, QString major, int yr, Support support);
    QString getClassName() const;
    QString toString() const;
protected:
    static QString supportStr(Support sup);
private:
    Support m_support;
};



#endif
