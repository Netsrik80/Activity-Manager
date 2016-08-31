#ifndef MANAGER_DATASERVICE_H
#define MANAGER_DATASERVICE_H

#include "dataservice.h"
#include "entity.h"
#include <QMultiMap>

class Manager_Dataservice : public Dataservice
{

private:

    void init_man();

    QMap< int, QString > studs_map; //1
    QMap< int, QString > acts_map; //2
    QMultiMap< int, int > combi_studkey_mmap; //3 = map for saving!
    QMultiMap< int, int > combi_actkey_mmap; //4

    QMap< int, QString > active_map;
    QMultiMap< int, int > active_mmap;
    int active_map_number;

    void set_map_toActive(int);
    void switch_active_map();
    void switch_active_mmap();
    void copy_activeMap();

    Entity aStudent;
    Entity aClass;
    bool first_is_aStudent;

public:

    Manager_Dataservice();

    QStringList get_all_names(int);

    int get_ID_byName(QString); //priv?

    QString get_Name_byID(int);

    QString get_name(QString req);

    bool check_ID(int);

    bool send_first_choice(QString aName); //pub!

    bool send_second_choice(QString aName);

    QStringList get_available_items(QString);

    bool join_clicked();

    bool leave_clicked();

    void erase(int);

    void save();

};

#endif // MANAGER_DATASERVICE_H
