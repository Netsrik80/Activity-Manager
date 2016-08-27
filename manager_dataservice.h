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

    QMultiMap< int, int > active_mmap;
    QMap< int, QString > active_map;
    int active_map_number;

    int active_KEY_forEdit;
    int active_VAL_forEdit;

    int active_editMode; //122 add; 211 remove
    int active_guiMode; //1 = students, 2=activities

    void init_man();

    void set_map_toActive(int);

    void set_mmap_toActive();

    void set_active_KEY(int);

    void switch_active_map();

    void switch_active_mmap();

    void copy_activeMap();


public:
    Manager_Dataservice();

    QMultiMap< int, int > get_mmap();

    QStringList get_all_names(int);

    QString get_Name_byID(int);

    int get_ID_byName(QString, QString);

    QStringList get_available_items();

    bool check_ID(int);


    void send_ID_toEdit(int);

    void do_edit_with(int);

    void set_editMode(QString);

    void set_guiMode(QString);

    void save();

};

#endif // MANAGER_DATASERVICE_H
