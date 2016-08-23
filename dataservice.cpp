///provides data for the gui, has access to fileowner

#include "dataservice.h"
#include "fileowner.h"
#include <iterator>
#include <QVariant>

using namespace std;

///public: constructor
Dataservice::Dataservice()
{

}


///public: setup data for the dataservice
void Dataservice::init(QString entType)
{
    Fileowner req2fileOwner;
    if(entType == "students")
    {
        curr_DB = req2fileOwner.studentsDB;
        req2fileOwner.get_Data(curr_DB);
        for(int i = 0; i < req2fileOwner.all2_Obj.size(); i++)
        {
            current_map.insert(req2fileOwner.all2_Obj[i].get_id(), req2fileOwner.all2_Obj[i].get_name());
        }
    }

    if(entType == "activites")
    {
        req2fileOwner.get_Data(req2fileOwner.activitiesDB);
        for(int i = 0; i < req2fileOwner.all2_Obj.size(); i++)
        {
            current_map.insert(req2fileOwner.all2_Obj[i].get_id(), req2fileOwner.all2_Obj[i].get_name());
        }
    }

}


///public: creates a string list from the current map (only values)
QStringList Dataservice::get_stringList()
{
        return current_map.values();

}


///public function to save changes
void Dataservice::save()
{
    add_data2file();
}


///private: automatically assignment of IDs
int Dataservice::create_ID()
{
    int newID = 1000;

    while(current_map.contains(newID))
    {
        newID += 1;
    }

    return newID;

}


///creation of a new object and insertion in map
void Dataservice::add_data(QString newName)
{
    TwoItemObject newEntry;
    newEntry.set_name(newName);
    newEntry.set_id(create_ID());

    current_map.insert(newEntry.get_id(), newEntry.get_name());

}


///removes an item or evoke an error-message for the user
bool Dataservice::remove_data(int id)
{
    if(current_map.remove(id) > 0)
    {
        return true;
    }

    return false;

}


///private: sends current data to the fileowner to save it in the file
void Dataservice::add_data2file()
{
    Fileowner saveRequest;
    saveRequest.set_Data(curr_DB, make_stringList_keysAndVals());

}


///changes a value in the map
void Dataservice::edit_data(QString name2change)
{
    current_map.insert(curr_id, name2change);

}


///public: returns an ID from map by an index of a QStringList and stores the ID, index of list and map should be the same...
int Dataservice::get_choosenMember(int index)
{
    QList< int > currList = current_map.keys();
    curr_id = currList[index];
    return curr_id;

}

///private: setup a QList<Strings> with keys and values to be sent to fileowner (add_Data2file)
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

///public:
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

