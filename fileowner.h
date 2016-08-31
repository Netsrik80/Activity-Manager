#ifndef FILEOWNER_H
#define FILEOWNER_H

#include "twoitemobject.h"
#include <QVector>
#include <QString>

using namespace std;

class Fileowner
{

private:
    void setDatabase();

    bool writeToFile(QString, QStringList);

    void readFromFile(QString);

public:
    Fileowner();

    QVector<TwoItemObject>vec_from_filedata;

    QString studentsDB; // public filename

    QString activitiesDB; // public filename

    QString combinationsDB; // public filename

    void get_Data(QString);

    bool set_Data(QString, QStringList);

};

#endif // FILEOWNER_H
