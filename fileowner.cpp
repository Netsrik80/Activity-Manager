/**
  * Handles the requests to files data
  * (only access to files)
  */

#include "fileowner.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>

using namespace std;

/// Setting of filenames
void Fileowner::setDatabase()
{
    studentsDB = "nameslist.csv";
    activitiesDB = "activitylist.csv";
    combinationsDB = "combinationslist.csv";
}


/// Constructor
Fileowner::Fileowner()
{
    setDatabase();
}


///Writes data (a QStringList) to the file
void Fileowner::writeToFile(QString reqFile, QStringList list)
{
    //open file
    QString filename (reqFile);
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&myfile);

    for(int i=0; i < list.size(); i++)
    {
        if(!list[i].isNull()) { out<< list[i]<<endl;}
    }

    //close file
    myfile.flush();
    myfile.close();
}


///Reads the data from the file and creates a QVector that contains objects with two values
void Fileowner::readFromFile(QString reqFile)
{
    //open file
    QString filename (reqFile);
    QFile myfile(filename);
    myfile.open(QIODevice::ReadWrite | QIODevice::Text);

    QTextStream inStream(&myfile);
    QString inLine;

    if(reqFile == combinationsDB)
    {
        //setup QVector (int, int) from file
        do{
            inLine = inStream.readLine();
            if(!inLine.isNull() && (inLine != "" ) )
            {
                QStringList strList;
                strList.append(inLine.split(","));
                QVariant id1 = strList[0];
                QVariant id2 = strList[1];

                TwoItemObject a2_Obj(id1.toInt(), id2.toInt());
                vec_from_filedata.append(a2_Obj);
            }
        }while(!inLine.isNull());
    }

    else
    {
        //setup QVector (int, string) from file
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
                vec_from_filedata.append(a2_Obj);
            }
        }while(!inLine.isNull());
    }

    //close file
    myfile.flush();
    myfile.close();
}


///Public function to get data from a file
void Fileowner::get_Data(QString file)
{
    readFromFile(file);
}


///Public function to send data to a file
void Fileowner::set_Data(QString file, QStringList list)
{
    writeToFile(file, list);
}
