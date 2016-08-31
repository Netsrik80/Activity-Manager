#ifndef MANAGER_DATASERVICE_H
#define MANAGER_DATASERVICE_H

#include "dataservice.h"
#include <QMultiMap>

class Manager_Dataservice : public Dataservice
{

private:
    QMap< int, QString > studs_map; //1
    QMap< int, QString > acts_map; //2
    QMultiMap< int, int > combi_studkey_mmap; //3 = map for saving!
    QMultiMap< int, int > combi_actkey_mmap; //4

    QMap< int, QString > active_map;
    QMultiMap< int, int > active_mmap;

    int active_map_number;
    int active_KEY_forEdit;
    int active_VAL_forEdit;
    int active_editMode; //122 add; 211 remove; 111 erase

    void init_man();

    void set_map_toActive(int);

    void switch_active_map();

    void switch_active_mmap();

    void copy_activeMap();

    void set_active_KEY(int);

    void set_active_VAL(int id_from_gui);


public:
    Manager_Dataservice();

    QMultiMap< int, int > get_mmap();

    QStringList get_all_names(int);

    QString get_Name_byID(int);

    QStringList get_available_items();

    int get_ID_byName(QString);

    int get_currentKey();

    int get_currentVal();

    bool check_ID(int);

    bool send_ID_toEdit(int);

    bool send_ID_editWith(int);

    bool do_edit_with(int);

    void set_editMode(QString);

    void save();

};

#endif // MANAGER_DATASERVICE_H
