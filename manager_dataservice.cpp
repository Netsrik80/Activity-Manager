#include "manager_dataservice.h"
#include "dataservice.h"
#include "fileowner.h"
#include <QStringList>
#include <QVariant>
#include <iterator>


using namespace std;

Manager_Dataservice::Manager_Dataservice()
{
    init_man();

}


/****************
 *    Setup     *
 *      &       *
 *   Settings   *
 * *************/

///Setup of QMultiMaps with student-IDs or activity-IDs as keys
void Manager_Dataservice::init_man()

{
    Fileowner req2fileOwner;

    ///Setup studs_map
    init("students");
    studs_map = get_map();

    ///Setup acts_map
    init("activities");
    acts_map = get_map();

    ///Setup combi-mmap with stud-IDs as keys
    req2fileOwner.get_Data(req2fileOwner.combinationsDB);
    for(int i = 0; i < req2fileOwner.vec_from_filedata.size(); i++)
    {
        if(!combi_actkey_mmap.contains(req2fileOwner.vec_from_filedata[i].get_id(), req2fileOwner.vec_from_filedata[i].get_id2()))
        {
            combi_studkey_mmap.insertMulti(req2fileOwner.vec_from_filedata[i].get_id(), req2fileOwner.vec_from_filedata[i].get_id2());
        }
    }

    ///Setup combi-mmap with act-IDs as keys
    req2fileOwner.get_Data(req2fileOwner.combinationsDB);
    for(int i = 0; i < req2fileOwner.vec_from_filedata.size(); i++)
    {
        if(!combi_actkey_mmap.contains(req2fileOwner.vec_from_filedata[i].get_id2(), req2fileOwner.vec_from_filedata[i].get_id()))
        {
            combi_actkey_mmap.insertMulti(req2fileOwner.vec_from_filedata[i].get_id2(), req2fileOwner.vec_from_filedata[i].get_id());
        }
    }

    /// Setup all member variables to initial values (studentsmode, no valid IDs set)
    active_guiMode = 1;     // initial value = students
    active_editMode = 211;  // initial value = remove
    active_KEY_forEdit = 0;
    active_VAL_forEdit = 0;
    set_map_toActive(1);
    set_mmap_toActive();

}


/// Settting: ID, wich ones values might be edit [priv]
void Manager_Dataservice::set_active_KEY(int id_from_gui)
{
    active_KEY_forEdit = id_from_gui;

}

/// Setting edit-mode [pub]
void Manager_Dataservice::set_editMode(QString editMode)
{
    if(editMode == "add") { active_editMode = 112; }

    if(editMode == "remove") { active_editMode = 211; }

}

/// Setting gui-mode [pub]
void Manager_Dataservice::set_guiMode(QString guiMode)
{
    if(guiMode == "students") { active_guiMode = 1; }

    if(guiMode == "activities") { active_guiMode = 2; }
}




/****************
 *    Map       *
 *  Management  *
 *              *
 * *************/

///Set one of the (at the moment 2) maps or multimaps as active_(m)map
void Manager_Dataservice::set_map_toActive(int map_number)
{
    switch (map_number) {

    case 1:
        active_map = studs_map;
        break;

    case 2:
        active_map = acts_map;
        break;

    case 3:
        active_mmap = combi_studkey_mmap;
        break;
    case 4:
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


/// Same as set
void Manager_Dataservice::set_mmap_toActive()
{
    int mmapNmbr = 4;

    if(active_guiMode == 1)
    {
        mmapNmbr = 3;
    }

    set_map_toActive(mmapNmbr);

}



///set that map to active, that is not the choosen one in gui
void Manager_Dataservice::switch_active_map()
{
    if(active_map_number == 1)
    {
        set_map_toActive(2);

    }
    else
    {
        set_map_toActive(1);

    }
}



///Setting of the not activated mult-map to active
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




/****************
 *              *
 *     get      *
 *              *
 * *************/


/// Returns multi-map [pub]
QMultiMap<int, int> Manager_Dataservice::get_mmap()
{
    return active_mmap;

}


/// Return of all available items (for right listView) [pub]
QStringList Manager_Dataservice::get_available_items()
{
    ///Setup of needed maps and variables
        /// active map
        if(active_guiMode == 1) { set_map_toActive(2); set_map_toActive(3); }
        /// active mulit-map
        if(active_guiMode == 2) { set_map_toActive(1); set_map_toActive(4); }
        QStringList strList;


    switch (active_editMode) {

        ///add-request
        case 112:
        {
                if(active_mmap.contains(active_KEY_forEdit))
                {
                    QList< int > keys_valList = active_mmap.values(active_KEY_forEdit);
                    QList< int > available_vals = active_map.keys();

                    /// Remove known students or activities
                    for(int i = 0; i < keys_valList.size(); i++)
                    {
                        available_vals.removeOne(keys_valList[i]);
                    }

                    /// Create a String-list from adjusted list
                    for(int i = 0; i < available_vals.size(); i++)
                    {
                        strList.append(active_map.value(available_vals[i]));
                    }
                }

                else{
                    strList = active_map.values();
                    }
         }break;

        ///remove-request
        case 211:
        {
                if(active_mmap.contains(active_KEY_forEdit))
                {
                    QList< int > keys_valList = active_mmap.values(active_KEY_forEdit);

                    for(int i = 0; i < keys_valList.size(); i++)
                    {
                        strList.append(active_map.value(keys_valList[i]));
                    }
                }
                else{
                    strList.append("No entry at the moment.");
                }
        }break;

        default:
        {
            qDebug("error get_available items");
        }break;

    }

    return strList;
}


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


/// Returns one value (QString) from a map (not multimap)
QString Manager_Dataservice::get_Name_byID(int key)
{
    if(key >= 1000) {set_map_toActive(1);}
    if(key < 1000) {set_map_toActive(2);}

    return active_map.value(key);

}


/// Returns the ID (int), that belongs to a name (QString)
int Manager_Dataservice::get_ID_byName(QString whoAsk, QString name)
{
    set_map_toActive(active_guiMode);
    if(whoAsk == "rightWidget") {switch_active_map();}

    return active_map.key(name);

}




/****************
 *              *
 *     set      *
 *              *
 * *************/

/// Setting of the KEY for edit [pub]
void Manager_Dataservice::send_ID_toEdit(int id_from_gui)
{ 
    set_active_KEY(id_from_gui);
    set_map_toActive(active_guiMode);
    set_mmap_toActive();

}



/// Check, if an entered ID is known [pub]
bool Manager_Dataservice::check_ID(int id)
{
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


/// Addition or removing of an ID from multi-maps [pub]
void Manager_Dataservice::do_edit_with(int id_from_gui)
{
    /// Setup of needed maps
    if(active_guiMode == 1) { set_map_toActive(3); }

    active_VAL_forEdit = id_from_gui;


    switch (active_editMode) {

    ///add
    case 112:
            active_mmap.insertMulti(active_KEY_forEdit, active_VAL_forEdit);
            copy_activeMap();

            switch_active_mmap();
            active_mmap.insertMulti(active_VAL_forEdit, active_KEY_forEdit);
            copy_activeMap();
            switch_active_mmap();

        break;

    ///remove
    case 211:
            active_mmap.remove(active_KEY_forEdit, active_VAL_forEdit);
            copy_activeMap();

            switch_active_mmap();
            active_mmap.remove(active_VAL_forEdit, active_KEY_forEdit);
            copy_activeMap();
            switch_active_mmap();

        break;

    default:
            qDebug("error in do edit");

        break;
    }
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
