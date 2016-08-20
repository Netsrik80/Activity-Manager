#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{

private:
    int id;
    QString name;

public:
    ///constructors (??? why do i need Student();)
    Student();
    Student(int, QString);

    ///set methods
    void set_name(QString);
    void set_id(int); //public?

    ///get methods
    int get_id();
    QString get_name();

};

#endif // STUDENT_H
