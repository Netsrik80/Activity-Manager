#include "manager_data_admin.h"
#include <QStringList>

using namespace std;

Manager_Data_Admin::Manager_Data_Admin()
{
    allStuds.init("students");
    allActs.init("activities");
    //combi_actKey.init();
    //combi_studKey.init();

}

///remove a student from an activity
///=remove act from student, remove student from act


///remove a

QStringList Manager_Data_Admin::get_studentslist()
{
    return allStuds.get_stringList();
}

QStringList Manager_Data_Admin::get_activitieslist()
{
    return allActs.get_stringList();
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
    qDebug("setmap");
    int startVal = 1;
    QStringList list = active_map.get_stringList();

    for(int i = 0; i < list.size(); i++)
    {
        QString curr_Nam = list[i];
        if(curr_Nam == name)
        {
            startVal = active_map.get_choosenMember(i);
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
