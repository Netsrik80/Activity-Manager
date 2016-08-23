#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "studentseditor.h"

using namespace std;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    qDebug("mainmenu Setup");

}


void MainMenu::on_pushButton_namesList_clicked()
{
    StudentsEditor studEdit;
    studEdit.exec();
    qDebug("exec studedit");

}


MainMenu::~MainMenu()
{
    delete ui;

}
