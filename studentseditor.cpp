#include "studentseditor.h"
#include "ui_studentseditor.h"
#include "dataservice.h"
#include "edit_name.h"
//#include "mainmenu.h"

using namespace std;

StudentsEditor::StudentsEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsEditor)
{
    ui->setupUi(this);
    dataRequest.init("students");
    setupQListView();

}


StudentsEditor::~StudentsEditor()
{
    delete ui;

}


void StudentsEditor::setupQListView()
{
    thisModel.setStringList(dataRequest.get_stringList());
    ui->QListView_allMembers->setModel(&thisModel);

}


void StudentsEditor::on_button_add_clicked()
{
    if(ui->lineEdit_newInput->text() != NULL)
    {
        dataRequest.add_data(ui->lineEdit_newInput->text());
        ui->lineEdit_newInput->clear();
    }
    else{
        ui->lineEdit_newInput->setText("please enter a text");
    }

    setupQListView();

}


void StudentsEditor::on_button_remove_clicked()
{
    if(ui->lineEdit_choosenItem->text() != NULL)
    {
            QVariant id_toDel = ui->lineEdit_choosenItem->text();

            if (dataRequest.remove_data(id_toDel.toInt()) == true)
            {
                ui->lineEdit_choosenItem->clear();
            }
            else{
                ui->lineEdit_choosenItem->setText("unknown ID");
                }

            setupQListView();
    }
    else{
        ui->lineEdit_choosenItem->setText("please enter ID");
    }

}


///
void StudentsEditor::on_QListView_allMembers_clicked(const QModelIndex &index)
{
    int index_clicked = index.row();
    QVariant received_id = dataRequest.get_choosenMember(index_clicked);
    ui->lineEdit_choosenItem->setText(received_id.toString());

}


///save data to file
void StudentsEditor::on_pushButton_save_clicked()
{
    dataRequest.save();
    this->close();

}

///input when pressing return
void StudentsEditor::on_lineEdit_newInput_returnPressed()
{
    on_button_add_clicked();

}

///new dialog to change the name (=value in the map)
void StudentsEditor::on_button_edit_clicked()
{
    QVariant req_ID = ui->lineEdit_choosenItem->text();
    if(ui->lineEdit_choosenItem->text() != NULL
            && dataRequest.isIDknown(req_ID.toInt()) == true)
    {
        QString newName;
        Edit_Name inputBox;
        inputBox.exec();
        newName = inputBox.get_name();
        dataRequest.edit_data(newName);
        setupQListView();
    }
    else{
        ui->lineEdit_choosenItem->setText("ID not found");
    }
}


///
void StudentsEditor::on_pushButton_search_clicked()
{
    if(dataRequest.get_stringList().contains(ui->lineEdit_search->text()))
    {
        for(int i = 0; i < dataRequest.get_stringList().size(); i++)
        {
            if(ui->lineEdit_search->text() == dataRequest.get_stringList().at(i))
            {
                on_QListView_allMembers_clicked(thisModel.index(i));
                ui->lineEdit_search->clear();

            }
        }
    }
    else{
        ui->lineEdit_search->setText("not found");
        ui->lineEdit_choosenItem->clear();
    }

}
