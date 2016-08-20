#ifndef FILEOWNER_H
#define FILEOWNER_H

#include "twoitemobject.h"
#include <QVector>
#include <QString>

using namespace std;

class Fileowner
{

private:
    void writeToFile(QString);
    void readFromFile(QString);
    void setDatabase();

public:
    Fileowner();

    void get_Data(QString);
    void set_Data(QString);

    QVector<TwoItemObject>all2_Obj;
    QString testString;

    ///Filenames
    QString studentsDB;
    QString activitiesDB;
};

#endif // FILEOWNER_H
