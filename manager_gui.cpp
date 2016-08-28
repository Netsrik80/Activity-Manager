/**
* Settings of all visible elements.
*
* The data settings are made by the
* Manager_Dataservice-Class not by this.
*
**/

#include "manager_gui.h"
#include "ui_manager_gui.h"
#include <QListWidget>
#include <QListWidgetItem>
#include "error_popup.h"


Manager_GUI::Manager_GUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager_GUI)
{
    ui->setupUi(this);
    on_pushButton_students_clicked();
    m_datatservice.set_editMode("remove");
    ui->pushButton_remove->setDisabled(1);
}


Manager_GUI::~Manager_GUI()
{
    delete ui;
}

/**
             ****************
             *              *
             *  Buttons     *
             *              *
             * **************
*/


///Button: Students
void Manager_GUI::on_pushButton_students_clicked()
{
    ui->pushButton_students->setDisabled(1);
    ui->pushButton_classes->setDisabled(0);

    mode = 1;
    m_datatservice.set_guiMode("students");
    setup_leftListWidget();

}


///Button: Classes
void Manager_GUI::on_pushButton_classes_clicked()
{
    ui->pushButton_students->setDisabled(0);
    ui->pushButton_classes->setDisabled(1);

    mode = 2;
    m_datatservice.set_guiMode("activities");
    setup_leftListWidget();

}


///Button: Enter
void Manager_GUI::on_pushButton_enter_clicked()
{
    QVariant req_ID = ui->lineEdit_enterID->text();
    if( (( (req_ID.toInt() >= 1000 && mode == 1) || (req_ID.toInt() < 1000 && mode == 2) )
         && (m_datatservice.check_ID(req_ID.toInt()) == true) ))
    {

        ///sends the id (student/activity) and sets the corresponding combi-list (mmap) to active
        m_datatservice.send_ID_toEdit(req_ID.toInt());

        ui->lineEdit_search->setText(m_datatservice.get_Name_byID(req_ID.toInt()));
        setup_rightListWidget();

    }
    else{
        Error_popup error;
        error.set_text("ID unknown");
        error.exec();
    }

}


///Add Button
void Manager_GUI::on_pushButton_add_to_clicked()
{
    if(ui->lineEdit_enterID->text() == 0)
    {
        Error_popup err;
        err.set_text("Information incomplete!");
        err.exec();
    }
    else{
        ui->pushButton_add_to->setDisabled(1);
        ui->pushButton_remove->setDisabled(0);

        ui->listWidget_inv_list->clear();
        m_datatservice.set_editMode("add");
        ui->pushButton_enter_inv->setText("add to");

        setup_rightListWidget();
        }

}


/// Remove Button
void Manager_GUI::on_pushButton_remove_clicked()
{

    ui->pushButton_add_to->setDisabled(0);
    ui->pushButton_remove->setDisabled(1);

    ui->listWidget_inv_list->clear();
    m_datatservice.set_editMode("remove");
    ui->pushButton_enter_inv->setText("remove from");

    setup_rightListWidget();


}


///Edit Button
void Manager_GUI::on_pushButton_enter_inv_clicked()
{
    QVariant req_ID = ui->lineEdit_enterID_inv->text();

    if(m_datatservice.check_ID(req_ID.toInt()) == true && (ui->lineEdit_enterID != 0))

    {
        m_datatservice.do_edit_with(req_ID.toInt());

        ui->lineEdit_enterID_inv->clear();
        ui->lineEdit_search_inv->clear();

        Error_popup message;
        message.set_text("Changes are cached. Continue or save.");
        message.exec();
    }

    else{
        Error_popup error;
        error.set_text("Information inclompete!");
        error.exec();
    }

     setup_rightListWidget();

}

/// Save button
void Manager_GUI::on_pushButton_save_clicked()
{
    m_datatservice.save();
    this->close();

}

/// Exit button
void Manager_GUI::on_pushButton_exit_clicked()
{
    this->close();

}

/**
             ****************
             *              *
             *    lists     *
             *              *
             * **************
*/

///Left ListWidget (view)
void Manager_GUI::setup_leftListWidget()
{         
    ui->listWidget_list->clear();
    switch (mode) {

    case 1:
        ui->listWidget_list->clear();
        ui->listWidget_list->addItems(m_datatservice.get_all_names(mode));
        ui->label->setText("Name: ");
        break;

    case 2:
        ui->listWidget_list->clear();
        ui->listWidget_list->addItems(m_datatservice.get_all_names(mode));
        ui->label->setText("Activity: ");
        break;

    default:
        ui->listWidget_list->addItem("no list available");
        break;
    }

}


///Left ListWidget (action)
void Manager_GUI::on_listWidget_list_itemClicked(QListWidgetItem *item)
{
    QString clicked_name = item->text();
    QVariant id = m_datatservice.get_ID_byName("leftWidget", clicked_name);
    ui->lineEdit_enterID->setText(id.toString());
    ui->lineEdit_search->setText(item->text());

    m_datatservice.send_ID_toEdit(id.toInt());


    clear_editor();
    on_pushButton_remove_clicked();


}


///Right ListWidget
void Manager_GUI::setup_rightListWidget()
{
    ui->listWidget_inv_list->clear();
    ui->listWidget_inv_list->addItems(m_datatservice.get_available_items());

    ui->lineEdit_enterID_inv->setDisabled(0);
    ui->pushButton_enter_inv->setDisabled(0);

}


///Right ListWidget (action)
void Manager_GUI::on_listWidget_inv_list_itemClicked(QListWidgetItem *item)
{
    QString clicked_name = item->text();

    QVariant id = m_datatservice.get_ID_byName("rightWidget", clicked_name);
    ui->lineEdit_search_inv->setText(clicked_name);
    ui->lineEdit_enterID_inv->setText(id.toString());

}


/**
             ****************
             *              *
             *    input     *
             *              *
             * **************
*/


/// Left id-input-field (action)
void Manager_GUI::on_lineEdit_enterID_cursorPositionChanged(int arg1, int arg2)
{
    arg1 = curr_curspos_ent1;
    ui->listWidget_list->setCurrentRow(-1);
    arg2 = ui->lineEdit_enterID->cursorPosition();
    curr_curspos_ent1 = arg2;
    clear_editor();
    ui->lineEdit_search->clear();
}


/// Right id-input-field (action)
void Manager_GUI::on_lineEdit_enterID_inv_cursorPositionChanged(int arg1, int arg2)
{
    arg1 = curr_curspos_ent2;
    ui->listWidget_inv_list->setCurrentRow(-1);
    arg2 = ui->lineEdit_enterID_inv->cursorPosition();
    curr_curspos_ent2 = arg2;

}


/// Removing of all entrys in the editor
void Manager_GUI::clear_editor()
{
    ui->lineEdit_enterID_inv->clear();
    ui->lineEdit_search_inv->clear();
    ui->listWidget_inv_list->clear();

}

