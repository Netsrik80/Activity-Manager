///provides data, access to fileowner

#include "dataservice.h"
#include "fileowner.h"

using namespace std;

Dataservice::Dataservice()
{

}

Dataservice::Dataservice()
{

}

/*//creates vectors from files = make Vector
void Dataservice::make_vector(QString entType)
{    
    if(entType == "students")
    {
    Fileowner access2studs;
    access2studs.get_Data(access2studs.studentsDB);
    current_Vec = access2studs.all2_Obj;
    }

    if(entType == "activites")
    {
    Fileowner access2acts;
    access2acts.get_Data(access2acts.activitiesDB);
    act_Vec = access2acts.all2_Obj;
    }
    qDebug("made studVec");

}
*/

//select on of the vectors, that has been made by make_vector()
QVector<TwoItemObject> Dataservice::set_vector(QString entType)
{
    if(entType == "students")
    {
        qDebug("stud_Vec");
        return stud_Vec;

    }

    if(entType == "activities")
    {
        return act_Vec;

    }else{
        qDebug("no vector available");

    }
}

QStringList Dataservice::get_stringList(QString entType)
{
        qlist_onlyNames.clear();
        QVariant vecSize = set_vector(entType).size();

        qDebug("qlist_names clear");

        for(int i = 0; i < set_vector(entType).size(); i++)
        {
            QVariant id = set_vector(entType)[i].get_id();
            qlist_onlyNames.insert(i, "ID: "+id.toString()+", "+"Name: "+set_vector(entType)[i].get_name());
            qDebug("setup a stringlist");
        }

   return qlist_onlyNames;

}


int Dataservice::create_ID(QString entType)
{
    int newID = 1000;

    for(int i = 0; i < set_vector(entType).size(); i++)
    {
        if(set_vector(entType)[i].get_id() == newID)
        {
            qDebug("newID");
            newID += 1;
        }
    }

    return newID;

}



void Dataservice::add_data2vec(QString entType, QString newName)
{
    TwoItemObject newEntry;
    newEntry.set_name(newName);
    newEntry.set_id(create_ID(entType));

    ///set_vector does not work - why???
    if(entType =="students")
    {
        stud_Vec.append(newEntry);
        qDebug("did new entry");
    }

    if(entType == "activities")
    {
        act_Vec.append(newEntry);

    }
}

bool Dataservice::remove_dataFromVec(QString entType, int id)
{
    ///set_vector does not work - why???
    if(entType =="students")
    {
        for(int i = 0; i < stud_Vec.size(); i++)
        {
            if(stud_Vec[i].get_id() == id)
            {
                stud_Vec.remove(i);
                qDebug("enter if");
                return true;
            }

            if(i+1 == stud_Vec.size())
            {
                return false;
            }
        }

    }

    if(entType == "activities")
    {
        for(int i = 0; i < act_Vec.size(); i++)
        {
            if(act_Vec[i].get_id() == id)
            {
                act_Vec.remove(i);
                return 0;
                break;
            }
            else{
                return 1;
                }
        }

    }

    get_stringList(entType);

}


void Dataservice::add_data2file(QString entType)
{
    Fileowner saveRequest;
    for(int i = 0; i < set_vector(entType).size(); i++)
    {
       QVariant id = set_vector(entType)[i].get_id();
       qlist_toFile.append(id.toString()+","+set_vector(entType)[i].get_name());
    }
    saveRequest.set_Data(saveRequest.studentsDB, qlist_toFile);

}

int Dataservice::get_selected_ID()
{
    return this->selected_ID;
}

void Dataservice::change_Name(QString entType, QString name2change)
{
    for(int i = 0; i < stud_Vec.size(); i++)
    {
        qDebug("ID not found");
        if(stud_Vec[i].get_id() == this->selected_ID)
        {
            stud_Vec[i].set_name(name2change);
            break;
        }
        if(i+1 == stud_Vec.size())
        {
            qDebug("ID not found");
        }
    }
}
