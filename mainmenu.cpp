#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "studentseditor.h"


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
    studEdit.show();
}
