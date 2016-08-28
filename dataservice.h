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

    int start_ID;

    QString curr_DB;

    int curr_id;

    void add_data2file();

    QStringList make_strList_for_add_data2file();

    int create_ID();

    bool remove_warning;

    QList<int> remove_container; /// Storage to be used to keep DBs consistent

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

};

#endif // DATASERVICE_H
