#ifndef DATASERVICE_H
#define DATASERVICE_H

//#include "fileowner.h"

#include "twoitemobject.h"
//#include <QStringList>
#include <QStringListModel>
#include <QVector>


class Dataservice
{
private:
    void sendToFileOwner();
    void receiveFromFileOwner();
    void makeQSLmodel(QStringList);

    QVector<TwoItemObject> stud_Vec;
    QVector<TwoItemObject> act_Vec;

    int create_ID(QString);

public:
    Dataservice();    

    QStringList qlist_onlyNames;
    QStringList qlist_toFile;
    QStringListModel model;

    //QStringListModel modelForActs;


    QVector<TwoItemObject> set_vector(QString);
    QStringList get_stringList(QString);
    void make_vector(QString);

    bool remove_dataFromVec(QString entType, int indx);
    void add_data2vec(QString, QString);

    void add_data2file(QString); //?

    int selected_ID;
    int get_selected_ID();
    void change_Name(QString, QString);


    QString testString;
};

#endif // DATASERVICE_H
