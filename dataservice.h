#ifndef DATASERVICE_H
#define DATASERVICE_H

#include "fileowner.h"
#include "twoitemobject.h"
#include <QMap>

class Dataservice
{
private:
    QMap< int, QString > current_map;
    QMultiMap< int, int > current_mmap;
    int curr_id;
    int curr_val;/// for multimap
    QString curr_DB;
    int start_ID;

    void add_data2file();
    QStringList make_stringList_keysAndVals();
    int create_ID();


public:
    Dataservice();
    void init(QString);
    //void init(QString, QString);
    void save();
    void add_data(QString);
    bool remove_data(int);
    bool edit_data(QString);
    bool isIDknown(int);
    QStringList get_stringList();
    int get_choosenMember(int);

};

#endif // DATASERVICE_H
