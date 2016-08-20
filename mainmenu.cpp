#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "fileowner.h"

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

///TestButton (writeToFile)
void MainMenu::on_pushButton_liste_1_clicked()
{
    Fileowner fileWriter;
    fileWriter.set_Data(fileWriter.studentNames);
}

///TestButton (getDatafromFile, Setup Object)
void MainMenu::on_pushButton_liste_2_clicked()
{
    Fileowner fileReader;
    fileReader.get_Data(fileReader.studentNames);
    ui->testAusgabe->setText(fileReader.testString);
}
