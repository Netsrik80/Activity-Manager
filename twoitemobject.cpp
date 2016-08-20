///Creates object with two values (int & QString)

#include "twoitemobject.h"

TwoItemObject::TwoItemObject()
{

}

TwoItemObject::TwoItemObject(int aNumber, QString aWord)
{
    set_id(aNumber);
    set_name(aWord);
}

void TwoItemObject::set_id(int number)
{
    id = number;
}

void TwoItemObject::set_name(QString word)
{
    name = word;
}

int TwoItemObject::get_id()
{
    return id;
}

QString TwoItemObject::get_name()
{
    return name;
}
