#include "studentseditor.h"
#include "ui_studentseditor.h"
#include "twoitemobject.h"
#include "dataservice.h"
#include "edit_name.h"
#include "mainmenu.h"

using namespace std;


StudentsEditor::StudentsEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsEditor)
{
    ui->setupUi(this);
    thisEntType = "students";
    dataRequest.make_vector(thisEntType);
    setupQListView();
    qDebug("studedit setup finished");
}

StudentsEditor::~StudentsEditor()
{
    delete ui;
}

void StudentsEditor::setupQListView()
{
    thisModel.setStringList(dataRequest.get_stringList(thisEntType));
    ui->QListView_allMembers->setModel(&thisModel);
    qDebug("qlistview_Setup");
}


void StudentsEditor::on_button_add_clicked()
{
    if(ui->lineEdit_newInput->text() != NULL)
    {
        dataRequest.add_data2vec(thisEntType, ui->lineEdit_newInput->text());
        qDebug("add Data to vec done");
        //ui->testLabel->setText(dataRequest.set_vector(thisEntType)[0].get_name());
        ui->lineEdit_newInput->clear();
        setupQListView();
    }
}

void StudentsEditor::on_button_remove_clicked()
{
    QVariant id_toDel = ui->lineEdit_choosenItem->text();
    dataRequest.selected_ID = id_toDel.toInt();
    if (dataRequest.remove_dataFromVec(thisEntType, dataRequest.selected_ID) == true)
    {
        ui->lineEdit_choosenItem->clear();
    }
    else{
        ui->lineEdit_choosenItem->setText("unknown ID");
    }
    setupQListView();
}


void StudentsEditor::on_QListView_allMembers_clicked(const QModelIndex &index)
{
    int index_clicked = index.row();
    dataRequest.selected_ID = dataRequest.set_vector(thisEntType)[index_clicked].get_id();
    QVariant currentID = dataRequest.selected_ID;
    ui->lineEdit_choosenItem->setText(currentID.toString());

}

void StudentsEditor::on_pushButton_save_clicked()
{
    dataRequest.add_data2file(thisEntType);
    this->close();

}


void StudentsEditor::on_lineEdit_newInput_returnPressed()
{
    on_button_add_clicked();

}

void StudentsEditor::on_button_edit_clicked()
{
    QString newName;
    Edit_Name inputBox;
    inputBox.exec();
    newName = inputBox.get_name();
    dataRequest. change_Name(thisEntType, newName);
    setupQListView();
}
