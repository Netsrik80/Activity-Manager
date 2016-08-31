/**
  * Objecttype
  */

#include "twoitemobject.h"

using namespace std;


TwoItemObject::TwoItemObject()
{

}


TwoItemObject::TwoItemObject(int aNumber, QString aWord)
{
    set_id(aNumber);
    set_name(aWord);
    set_id2(0);
}


TwoItemObject::TwoItemObject(int studID, int actID)
{
    set_id(studID);
    set_id2(actID);
    set_name("");
}


void TwoItemObject::set_id(int number)
{
    id = number;
}


int TwoItemObject::get_id()
{
    return id;
}


void TwoItemObject::set_id2(int number)
{
    id2 = number;
}


int TwoItemObject::get_id2()
{
    return id2;
}


void TwoItemObject::set_name(QString word)
{
    name = word;
}


QString TwoItemObject::get_name()
{
    return name;
}
