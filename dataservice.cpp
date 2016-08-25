///Provides data for the GUIs

#include "dataservice.h"
#include "fileowner.h"
#include <iterator>
#include <QVariant>

using namespace std;

Dataservice::Dataservice()
{

}


///Setup of the map with required data
void Dataservice::init(QString entType)
{
    Fileowner req2fileOwner;
    if(entType == "students")
    {
        curr_DB = req2fileOwner.studentsDB;
        start_ID = 1000;
        req2fileOwner.get_Data(curr_DB);
        for(int i = 0; i < req2fileOwner.all2_Obj.size(); i++)
        {
            current_map.insert(req2fileOwner.all2_Obj[i].get_id(), req2fileOwner.all2_Obj[i].get_name());
        }
    }

    if(entType == "activities")
    {
        curr_DB = req2fileOwner.activitiesDB;
        start_ID = 100;
        req2fileOwner.get_Data(req2fileOwner.activitiesDB);
        for(int i = 0; i < req2fileOwner.all2_Obj.size(); i++)
        {
            current_map.insert(req2fileOwner.all2_Obj[i].get_id(), req2fileOwner.all2_Obj[i].get_name());
        }
        qDebug("done init");
    }

    if(entType == "combinations")
    {
        curr_DB = req2fileOwner.combinationsDB;
        //start_ID = 100;
        req2fileOwner.get_Data(req2fileOwner.combinationsDB);
        for(int i = 0; i < req2fileOwner.all2_Obj.size(); i++)
        {
            current_map.insert(req2fileOwner.all2_Obj[i].get_id(), req2fileOwner.all2_Obj[i].get_name());
        }
        qDebug("done init");
    }

}


///Creates a string list of the values of the current map
QStringList Dataservice::get_stringList()
{
        return current_map.values();

}


///Public access to save data to file
void Dataservice::save()
{
    add_data2file();

}


///Determining of an new ID
int Dataservice::create_ID()
{
    int newID = start_ID;

    while(current_map.contains(newID))
    {
        newID += 1;
                if(newID >= start_ID*10)
        {
    }

    return newID;

}


///Object creation and insertion to map
void Dataservice::add_data(QString newName)
{
    TwoItemObject newEntry;
    newEntry.set_name(newName);
    newEntry.set_id(create_ID());

    current_map.insert(newEntry.get_id(), newEntry.get_name());

}


///Removes an item from map or evoke an error-message for the user
bool Dataservice::remove_data(int id)
{
    if(current_map.remove(id) > 0)
    {
        return true;
    }

    return false;

}


///Sends data to fileOwner
void Dataservice::add_data2file()
{
    Fileowner saveRequest;
    saveRequest.set_Data(curr_DB, make_stringList_keysAndVals());

}


///Changing of values in map
bool Dataservice::edit_data(QString name2change)
{
    if(!get_stringList().contains(name2change))
    {
             current_map.insert(curr_id, name2change);
             return true;
    }
    else{
             return false;
        }

}


///Return of an ID and storing that ID as current ID
int Dataservice::get_choosenMember(int index)
{
    QList< int > currList = current_map.keys();
    curr_id = currList[index];
    return curr_id;
    qDebug("return");

}

///Creation of a string list of keys, comma and value
QStringList Dataservice::make_stringList_keysAndVals()
{
    QStringList keysAndVals_List;
    QMap < int, QString > ::iterator i = current_map.begin();
    while( i != current_map.end())
    {
        QVariant theKey = i.key();
        keysAndVals_List.append(theKey.toString()+","+i.value());
        i++;
    }

    return keysAndVals_List;

}

///Check, if an given ID is known
bool Dataservice::isIDknown(int req_ID)
{
    if(current_map.contains(req_ID) == true)
    {
            return true;
    }
    else{
          return false;
    }

}

