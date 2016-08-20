#ifndef FILEOWNER_H
#define FILEOWNER_H

#include "student.h"
#include <QVector>
#include <QString>

using namespace std;

class Fileowner
{

private:
    void writeToFile(QString);
    void readFromFile(QString);

    ///Filenames
    //QString studentNamesDB = "nameslist.csv";

public:
    Fileowner();

    void get_Data(QString);
    void set_Data(QString);

    QVector<Student> allStudents;
    QString testString;

    ///public Filenames
    //QString studentNames = studentNamesDB;
    QString studentNames = "nameslist.csv";
};

#endif // FILEOWNER_H
