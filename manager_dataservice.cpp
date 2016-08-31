/**
  * Datamanagement for the manager_gui
  */

#include "manager_dataservice.h"
#include "dataservice.h"
#include "fileowner.h"
#include "entity.h"
#include <QStringList>
#include <QVariant>
#include <iterator>
#include <QDebug>

using namespace std;

Manager_Dataservice::Manager_Dataservice()
{
    init_man();

}

/*
             ****************
             *              *
             *     init     *
             *              *
             * **************
*/

///Setup of QMultiMaps with student-IDs or activity-IDs as keys
void Manager_Dataservice::init_man()
{
    Fileowner req2fileOwner;

    // Setup studs_map
    init("students");
    studs_map = get_map();

    // Setup acts_map
    init("activities");
    acts_map = get_map();

    // Setup combi-mmap with stud-IDs as keys
    req2fileOwner.get_Data(req2fileOwner.combinationsDB);
    for(int i = 0; i < req2fileOwner.vec_from_filedata.size(); i++)
    {
        if(!combi_studkey_mmap.contains(req2fileOwner.vec_from_filedata[i].get_id(), req2fileOwner.vec_from_filedata[i].get_id2())
                && (req2fileOwner.vec_from_filedata[i].get_id2() != 0) )
        {
            combi_studkey_mmap.insertMulti(req2fileOwner.vec_from_filedata[i].get_id(), req2fileOwner.vec_from_filedata[i].get_id2());
        }
    }

    // Setup combi-mmap with act-IDs as keys
    req2fileOwner.get_Data(req2fileOwner.combinationsDB);
    for(int i = 0; i < req2fileOwner.vec_from_filedata.size(); i++)
    {
        if(!combi_actkey_mmap.contains(req2fileOwner.vec_from_filedata[i].get_id2(), req2fileOwner.vec_from_filedata[i].get_id())
                && (req2fileOwner.vec_from_filedata[i].get_id() != 0) )
        {
            combi_actkey_mmap.insertMulti(req2fileOwner.vec_from_filedata[i].get_id2(), req2fileOwner.vec_from_filedata[i].get_id());
        }
    }

}


/*
             ****************
             *  private map *
             *  management  *
             *              *
             * **************
*/

///Set one of the (at the moment 2) maps or multimaps as active_(m)map
void Manager_Dataservice::set_map_toActive(int map_number)
{
    switch (map_number) {

    case 1:
        active_map.clear();
        active_map = studs_map;
        break;

    case 2:
        active_map.clear();
        active_map = acts_map;
        break;

    case 3:
        active_mmap.clear();
        active_mmap = combi_studkey_mmap;
        break;
    case 4:
        active_mmap.clear();
        active_mmap = combi_actkey_mmap;
        break;

    default:
        qDebug("acitve map is not set correct");
        break;
    }

    active_map_number = map_number;

}


/// Make a copy from active map to the original map (maybe pointers would have been better?)
void Manager_Dataservice::copy_activeMap()
{
    switch (active_map_number) {

    case 1:
        studs_map = active_map;

        break;
    case 2:
        acts_map = active_map;

        break;
    case 3:
        combi_studkey_mmap = active_mmap;

        break;
    case 4:
        combi_actkey_mmap = active_mmap;

        break;
    default:
        qDebug("acitve map is not set correct");
        break;
    }

}


/// Set that map to active, that is not the choosen one in gui
void Manager_Dataservice::switch_active_map()
{
    if(active_map_number == 1)
    {
        set_map_toActive(2);

    }
    else{
        set_map_toActive(1);

    }
}


/// Setting of the not activated mult-map to active
void Manager_Dataservice::switch_active_mmap()
{
    if(active_map_number == 3)
    {
        set_map_toActive(4);

    }
    else{
        set_map_toActive(3);

    }
}



/*
             ****************
             *    public    *
             *    get/set   *
             *              *
             * **************
*/

/// Returns all values (QStringList) from a map (not multimap)
QStringList Manager_Dataservice::get_all_names(int mapnmbr)
{
    set_map_toActive(mapnmbr);

    QStringList str_list;

    if(mapnmbr < 3)
    {
        QMap < int, QString >::iterator it = active_map.begin();

        while(it != active_map.end())
        {
            QString str = it.value();
            str_list.append(str);
            it++;
        }
    }
    else{
        str_list.append("error");
    }

    return str_list;
}


/// Returns the ID (int), that belongs to a name (QString) (not multimap)
int Manager_Dataservice::get_ID_byName(QString name)
{
    // Maybe slow
    if(active_map.key(name) == 0)
    {
        switch_active_map();
        if(active_map.key(name) == 0) {return 0;}
    }

    return active_map.key(name);

}


/// Check, if an entered ID is known [pub]
bool Manager_Dataservice::check_ID(int id)
{
    if(id == 0)
    {
        return false;
    }

    if(id >= 1000 && !studs_map.contains(id))
    {
        return false;
    }

    if(id < 1000 && !acts_map.contains(id))
    {
        return false;
    }

    return true;
}


/// Return of the current name of aStudent or aClass
QString Manager_Dataservice::get_name(QString req)
{
    if(req == "student"){ return aStudent.get_name();}
    if(req == "class")  { return aClass.get_name(); }
    return "error";

}


/// Returns one value (QString) from a map (not multimap)
QString Manager_Dataservice::get_Name_byID(int key)
{
    if(key >= 1000) {set_map_toActive(1);}
    if(key < 1000) {set_map_toActive(2);}

    return active_map.value(key);

}


/// Init of aStudent or a aClass (1st input)
bool Manager_Dataservice::send_first_choice(QString aName)
{
    int new_ID = get_ID_byName(aName);

    if(check_ID(new_ID))
    {

        if(new_ID < 1000)
        {
            aClass.setup(new_ID, studs_map, acts_map, combi_actkey_mmap);
            first_is_aStudent = false;
            return true;
        }

        if(new_ID >= 1000)
        {
            aStudent.setup(new_ID, acts_map, studs_map, combi_studkey_mmap);
            first_is_aStudent = true;
            return true;
        }
    }

    return false;
}


/// Init of aStudent or a aClass (2nd input)
bool Manager_Dataservice::send_second_choice(QString aName)
{
    int new_ID = get_ID_byName(aName);

    if(check_ID(new_ID))
    {

        if(new_ID < 1000 && first_is_aStudent)
        {
            aClass.setup(new_ID, studs_map, acts_map, combi_actkey_mmap);
            return true;
        }

        if(new_ID >= 1000 && !first_is_aStudent)
        {
            aStudent.setup(new_ID, acts_map, studs_map, combi_studkey_mmap);
            return true;
        }
    }

    return false;
}


/// Return of all available items (for right listView) [pub]
QStringList Manager_Dataservice::get_available_items(QString kind_of)
{
    QString str;
    QStringList strList;

    if(kind_of == "available")
    {
        if(first_is_aStudent)
            for(int i = 0; i < aStudent.get_candidates().size(); i++)
            {
                str = get_Name_byID(aStudent.get_candidates().at(i) );
                strList.append(str);
            }
        else{
            for(int i = 0; i < aClass.get_candidates().size(); i++)
            {
                str = get_Name_byID(aClass.get_candidates().at(i) );
                strList.append(str);
            }
        }
    }


    if(kind_of == "associated")
    {

        if(first_is_aStudent)
            for(int i = 0; i < aStudent.get_associate().size(); i++)
            {
                str = get_Name_byID(aStudent.get_associate().at(i) );
                strList.append(str);
            }
        else{
            for(int i = 0; i < aClass.get_associate().size(); i++)
            {
                str = get_Name_byID(aClass.get_associate().at(i) );
                strList.append(str);
            }
        }
    }

    return strList;

}


/// Adds a new id to objects and maps
bool Manager_Dataservice::join_clicked()
{
    if(aStudent.grab(aClass.get_ID())){
        combi_studkey_mmap = aStudent.send_your_associates_to(combi_studkey_mmap);

        aClass.grab(aStudent.get_ID());
        combi_actkey_mmap = aClass.send_your_associates_to(combi_actkey_mmap);

        return true;
    }
    return false;

}


/// Adds a new id to objects and maps
bool Manager_Dataservice::leave_clicked()
{
    if(aStudent.release(aClass.get_ID()))
    {
        combi_studkey_mmap = aStudent.send_your_associates_to(combi_studkey_mmap);

        aClass.release(aStudent.get_ID());
        combi_actkey_mmap= aClass.send_your_associates_to(combi_actkey_mmap);

        return true;}
    return false;

}


/// Save data to file [pub]
void Manager_Dataservice::save()
{
    QMultiMap<int, int>::Iterator it = combi_studkey_mmap.begin();

    QVariant firstVal;
    QVariant secondVal;
    QStringList printList;

    while(it != combi_studkey_mmap.end())
    {
        firstVal = it.key();
        secondVal = it.value();
        printList.append(firstVal.toString() + "," + secondVal.toString());
        it++;
    }

    Fileowner saveReq;
    saveReq.set_Data("combinationslist.csv", printList);

}

/// Erase request from dataservice
void Manager_Dataservice::erase(int id)
{
    if(id >= 1000)
    {
        combi_studkey_mmap.remove(id);
    }

    if(id < 1000)
    {
        QMultiMap<int, int>::Iterator it = combi_studkey_mmap.begin();

        while(it != combi_studkey_mmap.end())
        {
            combi_studkey_mmap.remove(it.key(), id);
            it++;
        }

        save();
    }
}

