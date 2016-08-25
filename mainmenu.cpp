#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "studentseditor.h"
#include "activityeditor.h"
#include "manager_gui.h"

using namespace std;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

}


MainMenu::~MainMenu()
{
    delete ui;

}


void MainMenu::on_pushButton_namesList_clicked()
{
    StudentsEditor studEdit;
    studEdit.exec();

}


void MainMenu::on_pushButton_activityList_clicked()
{
    ActivityEditor actEdit;
    actEdit.exec();

}


void MainMenu::on_pushButton_actManager_clicked()
{
    Manager_GUI manager;
    manager.exec();

}
