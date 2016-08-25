#ifndef MANAGER_DATA_ADMIN_H
#define MANAGER_DATA_ADMIN_H

#include "dataservice.h"


class Manager_Data_Admin
{
private:
    Dataservice allStuds;
    Dataservice allActs;
    Dataservice combi_studKey;
    Dataservice combi_actKey;
    Dataservice active_map;/// 1=studs, 2=acts, 3=combistud, 4=combiact

    void set_map2active(int map_number);

    int key_id_toEdit;

public:
    Manager_Data_Admin();
    QStringList get_studentslist();
    QStringList get_activitieslist();
    int get_id_byName(int, QString);
    void set_key_id_toEdit(int, int);
};

#endif // MANNAGER_DATA_ADMIN_H
