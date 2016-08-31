#ifndef FILEOWNER_H
#define FILEOWNER_H

#include "twoitemobject.h"
#include <QVector>
#include <QString>

using namespace std;

class Fileowner
{

private:
    void writeToFile(QString, QStringList);

    void readFromFile(QString);

    void setDatabase();

public:
    Fileowner();

    void get_Data(QString);

    void set_Data(QString, QStringList);

    QVector<TwoItemObject>vec_from_filedata;

    ///public names for the files
    QString studentsDB;
    QString activitiesDB;
    QString combinationsDB;
};

#endif // FILEOWNER_H
