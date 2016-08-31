#include "entity.h"
#include <QList>
#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QVariant>
#include <QDebug>

using namespace std;

/// Constructor
Entity::Entity()
{
    id = 0;
    associates.clear();
    candidates.clear();
}


/// Setting of current joined classes or classmembers
bool Entity::set_associates(QMultiMap < int, int > home_multiMap)
{
    associates.clear();
    QList< int > associatesList = home_multiMap.values(id);

    for(int i = 0; i < associatesList.size(); i++)
    {
        associates.append(associatesList[i]);

    }

    return true;
}


/// Setting of available classes or available students
bool Entity::set_candidates(QMap< int, QString > other_map)
{
    candidates.clear();
    QList< int > allPossibilities = other_map.keys();

    for(int i = 0; i < associates.size(); i++)
    {
        if(allPossibilities.contains(associates[i]))
        {
            allPossibilities.removeOne(associates[i]);
        }

    }

    candidates = allPossibilities;

    return true;
}


/// Setting of the name
bool Entity::set_name(QMap < int, QString > home_map)
{
    name = home_map.value(id);
    return true;
}


/// Setup needs three maps (1.map=id=val; 2.map=id=key; 3.map=MultiMap=id=key)
bool Entity::setup(int new_id, QMap< int, QString > other_map, QMap< int, QString > home_map, QMultiMap< int, int > home_mulitMap)
{
    id = new_id;
    if(!set_name(home_map))             { return false; }
    if(!set_associates(home_mulitMap))  { return false; }
    if(!set_candidates(other_map))      { return false; }

    return true;

}


/// Return of the ID
int Entity::get_ID()
{
    return id;
}


/// Return of the name
QString Entity::get_name()
{
    return name;
}


/// Return of current joined classes or current members of a class
QList < int > Entity::get_associate()
{
    return associates;
}


/// Return of not joined classes or non-members of a class
QList < int > Entity::get_candidates()
{
    return candidates;
}


/// Entity get a new associate
bool Entity::grab(int id)
{
    if(!associates.contains(id))
    {
        associates.append(id);
        candidates.removeOne(id);

        return true;
    }
    return false;
}


/// Entity release an associate
bool Entity::release(int id)
{
    if(associates.contains(id))
    {
        associates.removeOne(id);
        candidates.append(id);
        return true;
    }
    return false;
}


/// Insertion of new values to the multiMap
QMultiMap< int, int > Entity::send_your_associates_to(QMultiMap< int, int > home_multiMap)
{
    for(int i = 0; i < associates.size(); i++)
    {
        if(!home_multiMap.contains(id, associates[i]) && id != 0)

        {
            home_multiMap.insertMulti(id, associates[i]);
        }
    }

    return home_multiMap;
}
