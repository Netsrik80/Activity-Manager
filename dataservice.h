#ifndef DATASERVICE_H
#define DATASERVICE_H

#include "fileowner.h"
#include "twoitemobject.h"
#include <QMap>
#include <QList>

class Dataservice
{
private:
    QMap< int, QString > current_map;
    int start_ID; /// for create_ID()
    QString curr_DB;

    int curr_id;
    int curr_val;/// for multimap

    void add_data2file();
    QStringList make_strList_for_add_data2file();
    int create_ID();


public:
    Dataservice();

    void init(QString);

    void add_data(QString);

    bool remove_data(int);

    bool edit_data(QString);

    void save();

    bool is_IDknown(int);

    int get_ID_clickedName_byModelIndex(int);

    QStringList get_strList_allValues();

    QMap< int, QString > get_map();



    QList< int > get_values_by_key();

    QList <int> get_key_list();


};

#endif // DATASERVICE_H
