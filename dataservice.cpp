///provides data, access to fileowner

#include "dataservice.h"
#include "fileowner.h"

Dataservice::Dataservice()
{

}

void Dataservice::getAllStudents()
{
    Fileowner access2studs;
    access2studs.get_Data(access2studs.studentsDB);
    stud_Vec = access2studs.all2_Obj;
    //testString = stud_Vec[0].get_name(); works!
}

void Dataservice::getAllActivities()
{

}

QStringList Dataservice::getQStringList_justNames(QVector<TwoItemObject> vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        stud_justNamesList.append(vec[i].get_name());
    }
    return stud_justNamesList;
}