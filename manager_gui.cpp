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
#include <QDebug>


Manager_GUI::Manager_GUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager_GUI)
{
    ui->setupUi(this);
    on_pushButton_students_clicked();
    ui->pushButton_students->setChecked(1);

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
    ui->pushButton_classes->setChecked(0);
    ui->lineEdit_KEY->clear();
    ui->listWidget_inv_list->clear();
    ui->lineEdit_enterID_inv->clear();

    mode = 1;

    setup_leftListWidget();

}


///Button: Classes
void Manager_GUI::on_pushButton_classes_clicked()
{
    ui->pushButton_students->setChecked(0);
    ui->lineEdit_KEY->clear();
    ui->listWidget_inv_list->clear();
    ui->lineEdit_enterID_inv->clear();

    mode = 2;

    setup_leftListWidget();

}


/// Enter first ID (key)
void Manager_GUI::on_pushButton_setKEY_clicked()
{
    QVariant key = ui->lineEdit_KEY->text();

    if(m_datatservice.send_ID_toEdit(key.toInt()) == false)
    {
            Error_popup error;
            error.set_text("ID unknown!");
            error.exec();
    }

    else
    {
        QVariant fresh_key = m_datatservice.get_currentKey();
        ui->lineEdit_currentKEY->setText(fresh_key.toString());
        ui->lineEdit_KEY->clear();
        ui->listWidget_list->setCurrentRow(-1);
    }

}




/// Available to add Button
void Manager_GUI::on_pushButton_show_addable_clicked()
{
    ui->pushButton_show_removable->setChecked(0);
    ui->pushButton_confirmADD->setChecked(0);
    ui->pushButton_confirmREM->setChecked(0);

    if(ui->lineEdit_currentKEY->text() == 0)
    {
        Error_popup err;
        err.set_text("Input of first ID is missing!");
        err.exec();
    }

    else{
        ui->lineEdit_KEY->clear();

        m_datatservice.set_editMode("add");
        setup_rightListWidget();

        }

}


/// Available to remove Button
void Manager_GUI::on_pushButton_show_removable_clicked()
{
    ui->pushButton_show_addable->setChecked(0);
    ui->pushButton_confirmADD->setChecked(0);
    ui->pushButton_confirmREM->setChecked(0);

    if(ui->lineEdit_currentKEY->text() == 0)
    {
        Error_popup err;
        err.set_text("Input of first ID is missing!");
        err.exec();
    }

    else{
        ui->lineEdit_KEY->clear();

        m_datatservice.set_editMode("remove");
        setup_rightListWidget();

        }

}


/// Set edit mode to add
void Manager_GUI::on_pushButton_confirmADD_clicked()
{
    ui->pushButton_confirmREM->setChecked(0);
    ui->pushButton_setVAL->setDisabled(1);
    m_datatservice.set_editMode("add");

    Error_popup mess;

    QVariant input = ui->lineEdit_currentVAL->text();
    if(m_datatservice.send_ID_editWith(input.toInt()) == true)
    {
        if(m_datatservice.do_edit_with(input.toInt()) == true)
        {
            setup_rightListWidget();
            ui->lineEdit_currentVAL->clear();

            mess.set_text("Modification cached!");
            mess.exec();
        }
        else
        {
            Error_popup err;
            err.set_text("ID is not available to add.");
            err.exec();
        }
    }
    else
    {
        mess.set_text("Modification not possible. Check input.");
        mess.exec();
    }

        ui->pushButton_setVAL->setDisabled(0);

}


/// Set edit mode to remove
void Manager_GUI::on_pushButton_confirmREM_clicked()
{
    ui->pushButton_confirmADD->setChecked(0);
    ui->pushButton_setVAL->setDisabled(1);
    m_datatservice.set_editMode("remove");

    Error_popup mess;

    QVariant input = ui->lineEdit_currentVAL->text();
    if(m_datatservice.send_ID_editWith(input.toInt()) == true)
    {
        if(m_datatservice.do_edit_with(input.toInt()) == true)
        {
            setup_rightListWidget();
            ui->lineEdit_currentVAL->clear();

            mess.set_text("Modification cached!");
            mess.exec();
        }
        else
        {
            Error_popup err;
            err.set_text("ID is not available to remove.");
            err.exec();
        }
    }
    else
    {
        mess.set_text("Modification not possible. Check input.");
        mess.exec();
    }

        ui->pushButton_setVAL->setDisabled(0);


}


/// Enter second ID (val)
void Manager_GUI::on_pushButton_setVAL_clicked()
{
    QVariant val = ui->lineEdit_enterID_inv->text();
    QVariant key = ui->lineEdit_currentKEY->text();

    if( (key.toInt() >= 1000 && val.toInt() < 1000)
            || (key.toInt() < 1000 && val.toInt() > 1000) )
    {
        if(m_datatservice.check_ID(val.toInt()) == false)
        {
            Error_popup error;
            error.set_text("ID is not available!");
            error.exec();
        }
        else
        {
            ui->lineEdit_currentVAL->setText(val.toString());
            ui->lineEdit_enterID_inv->clear();
        }

    }
    else
    {
        Error_popup error;
        error.set_text("Combination is not possible!");
        error.exec();
    }

    //ui->pushButton_setVAL->setDisabled(1);
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

        break;

    case 2:
        ui->listWidget_list->clear();
        ui->listWidget_list->addItems(m_datatservice.get_all_names(mode));

        break;

    default:
        ui->listWidget_list->addItem("no list available");

        break;
    }

}


///Left ListWidget (action)
void Manager_GUI::on_listWidget_list_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_inv_list->clear();
    ui->pushButton_show_addable->setChecked(0);
    ui->pushButton_show_removable->setChecked(0);

    QString clicked_name = item->text();
    int val = m_datatservice.get_ID_byName(clicked_name);

    if(val == 0 || m_datatservice.send_ID_toEdit(val) == false)
    {
        Error_popup error;
        error.set_text("ID unknown");
        error.exec();
    }

    else
    {
    QVariant fresh_val = m_datatservice.get_currentKey();
    ui->lineEdit_currentKEY->setText(fresh_val.toString());
    }

}


/// Right ListWidget (setup)
void Manager_GUI::setup_rightListWidget()
{
    ui->listWidget_inv_list->clear();
    ui->listWidget_inv_list->addItems(m_datatservice.get_available_items());

}


/// Right ListWidget (action)
void Manager_GUI::on_listWidget_inv_list_itemClicked(QListWidgetItem *item)
{
    QString clicked_name = item->text();

    if(!clicked_name.isNull() && clicked_name != "No entry at the moment.")
    {
        QVariant val = m_datatservice.get_ID_byName(clicked_name);
        ui->lineEdit_currentVAL->setText(val.toString());
    }
    else
        {
            Error_popup err;
            err.set_text("ID is incorrect!");
            err.exec();
        }

}
