#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "studentseditor.h"

using namespace std;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

}


void MainMenu::on_pushButton_namesList_clicked()
{
    StudentsEditor studEdit;
    studEdit.exec();

}


MainMenu::~MainMenu()
{
    delete ui;

}
