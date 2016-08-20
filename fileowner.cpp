#include "fileowner.h"
#include <QString>
#include <QFile>
#include <QTextStream>

using namespace std;

void Fileowner::setDatabase()
{
    studentsDB = "nameslist.csv";
    //activitiesDB =
}

Fileowner::Fileowner()
{
    setDatabase();
}

///Writes data (a QStringList) to the file
void Fileowner::writeToFile(QString reqFile)
{
    ///data for testing
    QStringList testData;
    testData << "126,Max" << "124,Bärbel" << "125,Carola";

    ///open file
    QString filename (reqFile);
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&myfile);

    for(int i=0; i < testData.size(); i++)
    {
        out<< testData[i]<<endl;
    }

    ///close file
    myfile.flush();
    myfile.close();
}

///Reads the data from the file and creates a QVector that contains objects with two values (id & name)
void Fileowner::readFromFile(QString reqFile)
{
    ///open file
    QString filename (reqFile);
    QFile myfile(filename);
    myfile.open(QIODevice::ReadWrite | QIODevice::Text);

    QTextStream inStream(&myfile);

    ///setup QVector from file
    for(int i=0; i < 3; i++)
    {
        QString inLine = inStream.readLine();
        QStringList testList;
        testList.append(inLine.split(","));
        QVariant idVari = testList[0];
        QString name = testList[1];
        int id = idVari.toInt();

        TwoItemObject a2_Obj(id, name);
        all2_Obj.append(a2_Obj);
    }

    testString = all2_Obj[2].get_name();

    ///close file
    myfile.flush();
    myfile.close();
}

void Fileowner::get_Data(QString file)
{
    readFromFile(file);
}

void Fileowner::set_Data(QString file)
{
    writeToFile(file);
}
