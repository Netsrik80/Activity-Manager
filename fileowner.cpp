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
void Fileowner::writeToFile(QString reqFile, QStringList list)
{
    ///open file
    QString filename (reqFile);
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&myfile);

    for(int i=0; i < list.size(); i++)
    {
        out<< list[i]<<endl;
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
    QString inLine;

    ///setup QVector from file
    do{
        inLine = inStream.readLine();
        if(!inLine.isNull())
        {
            QStringList strList;
            strList.append(inLine.split(","));
            QVariant idVari = strList[0];
            QString name = strList[1];
            int id = idVari.toInt();

            TwoItemObject a2_Obj(id, name);
            all2_Obj.append(a2_Obj);
        }
    }while(!inLine.isNull());

    ///close file
    myfile.flush();
    myfile.close();
}

void Fileowner::get_Data(QString file)
{
    readFromFile(file);
}

void Fileowner::set_Data(QString file, QStringList list)
{
    writeToFile(file, list);
}
