/**
* @mainpage Grundlagen der Informatik 2: QT-Projekt
*
* @section sec1 Short description
* With this program you can combine data from two databases (in this case two csv-files) to
* another one. So all the data is stored in three csv-files.
*
* @section sec2 Structures
* There are three different levels in the program. First there is the level "Filehandling": Only one class (Fileowner)
* has access to the files. The second level is the datamanagement (Dataservice, Manager_Dataservice), where objects (e.g. own Objects (TwoItemObject, Entity), QMaps, QVectors, QMultiMaps)
* are created an edited and then there are the GUIs (StudentsEditor, ActivityEditor, Error_popup, MainMenu,
* Manager_GUI, Edit_Name), where the surface-design and the user interaction are implemented.
*
* @section sec3 Datamanagement
* As mentioned the datamanagement is one level in the program. The main task of this level is to keep the data consistent, while the user is editing data. This works so
* far (i think...). But the design of this level could be much better. There are some redundant functions and so on. Also the difference between the Dataservice and
* the Manager_Dataservice became unclear, while programming. Also the use of the own object (TwoItemObject) is sometimes unclear. This should be revised.
*
* @section sec4 GITHUB
*
* You can find the code here:
*
* https://github.com/Netsrik80/Activity-Manager.git
*
* @author Kirsten Waller, Matrikelnummer 14 90 160, Juli/August 2016
*/

#include "mainmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu w;
    w.show();

    return a.exec();

}
