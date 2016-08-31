/**
  * Datamanagement for students- and activityeditor
  */

#include "dataservice.h"
#include "fileowner.h"
#include "manager_dataservice.h"
#include <iterator>
#include <QVariant>
#include <QStringList>

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
        current_map.clear();
        curr_DB = req2fileOwner.studentsDB;
        start_ID = 1000; //if this value would be changed, this (may) causes problems!!!
        req2fileOwner.get_Data(curr_DB);
        for(int i = 0; i < req2fileOwner.vec_from_filedata.size(); i++)
        {
            current_map.insert(req2fileOwner.vec_from_filedata[i].get_id(), req2fileOwner.vec_from_filedata[i].get_name());
        }
    }

    if(entType == "activities")
    {
        current_map.clear();
        curr_DB = req2fileOwner.activitiesDB;
        start_ID = 100; //if this value would be changed, this (may) causes problems!!!
        req2fileOwner.get_Data(req2fileOwner.activitiesDB);
        for(int i = 0; i < req2fileOwner.vec_from_filedata.size(); i++)
        {
            current_map.insert(req2fileOwner.vec_from_filedata[i].get_id(), req2fileOwner.vec_from_filedata[i].get_name());
        }
    }
    remove_warning == false;
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
        remove_warning = true;

        remove_container.append(id);

        return true;

    }

    return false;

}


/// Changing of values in map
bool Dataservice::edit_data(QString name2change)
{
    if((!get_strList_allValues().contains(name2change)) && (!name2change.isEmpty()))
    {
        current_map.insert(curr_id, name2change);
        return true;
    }
    else{
        return false;
    }

}


/// Public access to save data to file
void Dataservice::save()
{
    add_data2file();

}


/// Check, if an given ID is known
bool Dataservice::is_IDknown(int req_ID)
{
    if(current_map.contains(req_ID) == true)
    {
        return true;
    }
    else{
        return false;
    }

}


/// Return of an ID and storing that ID as current ID
int Dataservice::get_ID_clickedName_byModelIndex(int index)
{
    QList< int > currList = current_map.keys();
    curr_id = currList[index];
    return curr_id;

}


/// Creates a string list of the values of the this->map
QStringList Dataservice::get_strList_allValues()
{
    QStringList list = current_map.values();
    return list;
}


/// Return of map
QMap<int, QString > Dataservice::get_map()
{
    return current_map;
}


///private: Determining of an new ID
int Dataservice::create_ID()
{
    int newID = start_ID;

    while(current_map.contains(newID))
    {
        newID += 1;
        if(newID >= start_ID*10)
        {
            return 0;
            qDebug("error create_ID");
        }
    }

    return newID;

}


///private: Send data to save to fileOwner
void Dataservice::add_data2file()
{
    Fileowner saveRequest;
    saveRequest.set_Data(curr_DB, make_strList_for_add_data2file());

    if(remove_warning == true)
    {
        Manager_Dataservice update;
        update.save();

    }

}


///private: Creation of a string list of strings ("key,value")
QStringList Dataservice::make_strList_for_add_data2file()
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
