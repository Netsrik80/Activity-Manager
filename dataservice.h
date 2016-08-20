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

public:
    Dataservice();    
    QVector<TwoItemObject> stud_Vec;
    QVector<TwoItemObject> act_Vec;
    QStringList stud_justNamesList;
    QStringListModel model;
    //QStringListModel modelForActs;

    void getAllStudents();
    void getAllActivities();
    QStringList getQStringList_justNames(QVector<TwoItemObject>);


    QString testString;
};

#endif // DATASERVICE_H
