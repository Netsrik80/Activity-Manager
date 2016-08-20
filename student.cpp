#include "student.h"
#include <QString>

using namespace std;

Student::Student()
{

}

Student::Student(int aNumber, QString aWord)
{
    set_id(aNumber);
    set_name(aWord);
}

void Student::set_id(int number)
{
    id = number;
}

void Student::set_name(QString word)
{
    name = word;
}

int Student::get_id()
{
    return id;
}

QString Student::get_name()
{
    return name;
}
