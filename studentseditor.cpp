#include "studentseditor.h"
#include "ui_studentseditor.h"
#include "dataservice.h"
#include "mainmenu.h"

StudentsEditor::StudentsEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsEditor)
{
    ui->setupUi(this);
    setupQListView();
}

StudentsEditor::~StudentsEditor()
{
    delete ui;
}

void StudentsEditor::setupQListView()
{
    Dataservice dataRequest;
    dataRequest.getAllStudents();
    thisModel.setStringList(dataRequest.getQStringList_justNames(dataRequest.stud_Vec));
    ui->QListView_allMembers->setModel(&thisModel);

    ui->testLabel->setText(dataRequest.testString); //toDel
}

