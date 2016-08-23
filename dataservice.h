#ifndef DATASERVICE_H
#define DATASERVICE_H

#include "fileowner.h"
#include "twoitemobject.h"
#include <QMap>

class Dataservice
{
private:
    QMap< int, QString > current_map;
    int curr_id;
    QString curr_DB;

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
    void edit_data(QString);
    bool isIDknown(int);

    QStringList get_stringList();
    int get_choosenMember(int);

};

#endif // DATASERVICE_H
