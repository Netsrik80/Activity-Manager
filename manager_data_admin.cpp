#include "manager_data_admin.h"
#include <QStringList>

using namespace std;

Manager_Data_Admin::Manager_Data_Admin()
{
    allStuds.init("students");
    allActs.init("activities");
    combi_studKey.init("combinations"); ///first studs then acts
    combi_actKey.init("combinations_inv");

}

///remove a student from an activity
///=remove act from student, remove student from act



QStringList Manager_Data_Admin::get_studentslist()
{
    return allStuds.get_strList_allValues();
}

QStringList Manager_Data_Admin::get_activitieslist()
{
    return allActs.get_strList_allValues();
}


void Manager_Data_Admin::set_map2active(int map_number)
{
    switch (map_number) {
    case 1:
        active_map = allStuds;
        break;
    case 2:
        active_map = allActs;
        break;
    case 3:
        active_map = combi_studKey;
        break;
    case 4:
        active_map = combi_actKey;
        break;
    default:
        active_map = allStuds;
        qDebug("acitve map is not set correct");
        break;
    }
}

int Manager_Data_Admin::get_id_byName(int a, QString name)
{
    set_map2active(a);
    qDebug("man_dat_adm_set_map = mode");
    int startVal = 1;
    QStringList list = active_map.get_strList_allValues();

    for(int i = 0; i < list.size(); i++)
    {
        QString curr_Nam = list[i];
        if(curr_Nam == name)
        {
            startVal = active_map.get_ID_clickedName_byModelIndex(i);
            break;
        }
     }

    return startVal;
}

void Manager_Data_Admin::set_key_id_toEdit(int mode, int key)
{
    set_map2active(mode);
    key_id_toEdit = key;
}


///When add or remove clicked
QStringList Manager_Data_Admin::get_list_of_values_oneID(int mode)
{

    ///switch to one of the two mmaps
    if(mode == 1)
    {
        set_map2active(3);
        qDebug("man_dat_adm_set_map = 3");
    }
    else{
        set_map2active(4);
        qDebug("man_dat_adm_set_map = 4");
        }

    ///get al list of all values(int = ids of activities or students)
    QList< int > one_keys_value_list_from_mmap = active_map.get_values_by_key();

    ///switch from a mmap to one of the two maps (determined by mode)
    set_map2active(mode);
    qDebug("man_dat_adm_set_map = mode");

    QStringList str_list;

    for(int i = 0; i< one_keys_value_list_from_mmap.size(); i++)
    {
        int curr_key = one_keys_value_list_from_mmap[i];
    }

    return str_list;
    }


QStringList Manager_Data_Admin::get_list_of_non_values_oneID(int mode)
{

    ///switch to one of the two mmaps
    if(mode == 1)
    {
        set_map2active(3);
        qDebug("man_dat_adm_set_map = 3");
    }
    else{
        set_map2active(4);
        qDebug("man_dat_adm_set_map = 4");
    }

    ///get al list of all values(int = ids of activities or students)
    QList< int > one_keys_value_list_from_mmap = active_map.get_values_by_key();
    qDebug("man_dat_adm created a list of keys okay");

    ///switch from a mmap to one of the two maps (determined by mode)
    set_map2active(mode);
    qDebug("man_dat_adm_set_map = mode okay");

    QStringList str_list;

    ///create a map without the already known values
    QMap< int, QString > map_without_values = active_map.get_map();
    qDebug("ma_dat_adm copy of map");

    for(int i = 0; i< one_keys_value_list_from_mmap.size(); i++)
    {
        if(map_without_values.contains(one_keys_value_list_from_mmap[i]))
        {
            map_without_values.remove(one_keys_value_list_from_mmap[i]);
        }
    }


    QMap < int, QString > ::iterator it = map_without_values.begin();
    while( it != map_without_values.end())
    {
        str_list.append(it.value());
    }

    return str_list;
}
