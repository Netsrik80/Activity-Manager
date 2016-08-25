#include "activityeditor.h"
#include "ui_activityeditor.h"
#include "dataservice.h"
#include "edit_name.h"
#include "error_popup.h"

ActivityEditor::ActivityEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityEditor)
{
    ui->setupUi(this);
    dataRequest.init("activities");
    setupQListView();
}

ActivityEditor::~ActivityEditor()
{
    delete ui;
}


void ActivityEditor::setupQListView()
{
    thisModel.setStringList(dataRequest.get_stringList());
    ui->QListView_allMembers->setModel(&thisModel);
    qDebug("setupListView");

}


void ActivityEditor::on_button_remove_clicked()
{
    if(ui->lineEdit_choosenItem->text() != NULL)
    {
            QVariant id_toDel = ui->lineEdit_choosenItem->text();

            if (dataRequest.remove_data(id_toDel.toInt()) == true)
            {
                ui->lineEdit_choosenItem->clear();
            }
            else{
                Error_popup err;
                err.set_text("ID is unknown! Use list or search field above.");
                err.exec();
                }

            setupQListView();
    }
    else{
        Error_popup err;
        err.set_text("Entry missing! Please enter ID.");
        err.exec();
            }

}


///
void ActivityEditor::on_QListView_allMembers_clicked(const QModelIndex &index)
{
    int index_clicked = index.row();
    QVariant received_id = dataRequest.get_choosenMember(index_clicked);
    ui->lineEdit_choosenItem->setText(received_id.toString());

}

///save data to file
void ActivityEditor::on_pushButton_save_clicked()
{
    dataRequest.save();
    this->close();

}


///new dialog to change the name (=value in the map)
void ActivityEditor::on_button_edit_clicked()
{
    QVariant req_ID = ui->lineEdit_choosenItem->text();
    if(ui->lineEdit_choosenItem->text() != NULL
            && dataRequest.isIDknown(req_ID.toInt()) == true)
    {
        QString newName;
        Edit_Name inputBox;
        inputBox.exec();
        newName = inputBox.get_name();
        if(dataRequest.edit_data(newName) == true)
        {
        setupQListView();
        }
        else{
            Error_popup err;
            err.set_text("Change not possible. This entry already exists.");
            err.exec();
        }
    }
    else{
        Error_popup err;
        err.set_text("ID is unknown! Use list or search field above.");
        err.exec();
    }
}


///
void ActivityEditor::on_pushButton_search_clicked()
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
        ui->lineEdit_search->clear();
        Error_popup err;
        err.set_text("Not found! Check spelling or use the list above.");
        err.exec();

    }

}

void ActivityEditor::on_button_add_clicked()
{

    if(!dataRequest.get_stringList().contains(ui->lineEdit_newInput->text()))
    {
        if(ui->lineEdit_newInput->text() != NULL)
        {
            dataRequest.add_data(ui->lineEdit_newInput->text());
            ui->lineEdit_newInput->clear();
        }
        else{
            Error_popup err;
            err.set_text("Entry missing! Please enter a text.");
            err.exec();
            }
    }
    else{
            Error_popup err;
            err.set_text("This entry already exists. Change entry.");
            err.exec();
            }

    setupQListView();
}
