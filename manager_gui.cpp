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
#include <QCursor>

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


//************************************************* first input (left side)


///Button: Students
void Manager_GUI::on_pushButton_students_clicked()
{
    ui->pushButton_classes->setChecked(0);
    ui->lineEdit_KEY->clear();
    ui->listWidget_inv_list->clear();
    ui->lineEdit_currentVAL->clear();
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
    ui->lineEdit_currentVAL->clear();
    ui->lineEdit_enterID_inv->clear();

    mode = 2;

    setup_leftListWidget();

}

/// Upper list (all students or classes)
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


/// Release of the first enter button while typing
void Manager_GUI::on_lineEdit_KEY_cursorPositionChanged(int arg1, int arg2)
{
    ui->pushButton_enter->setDisabled(0);

}



/// Clicked on a student or a class in list
void Manager_GUI::on_listWidget_list_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_inv_list->clear();
    ui->pushButton_enter->setDisabled(1);
    ui->lineEdit_currentVAL->clear();

    QString clicked_name = item->text();

    if(clicked_name == 0 || m_datatservice.send_first_choice(clicked_name) == false)
    {
        Error_popup error;
        error.set_text("ID unknown");
        error.exec();
    }

    else
    {
        if(mode == 1)  {ui->lineEdit_currentKEY->setText(m_datatservice.get_name("student"));}
        if(mode == 2)  {ui->lineEdit_currentKEY->setText(m_datatservice.get_name("class"));}
        on_pushButton_show_removable_clicked();
    }

}



/// Enter left side
void Manager_GUI::on_pushButton_enter_clicked()
{
    QString input = ui->lineEdit_KEY->text();
    ui->listWidget_list->setCurrentRow(-1);

    if(m_datatservice.send_first_choice(input) == false)
    {
        Error_popup error;
        error.set_text("Sorry. Rejected request.");
        error.exec();
    }

    else
    {
        ui->lineEdit_currentKEY->setText(input);
        on_pushButton_show_removable_clicked();
        ui->listWidget_list->clear();

    }

}


//************************************************* second input (middle)


/// Available button
void Manager_GUI::on_pushButton_show_addable_clicked()
{
    ui->pushButton_show_removable->setChecked(0);
    ui->pushButton_show_addable->setChecked(1);
    ui->lineEdit_enterID_inv->clear();
    ui->pushButton_enter2->setDisabled(1);

    if(ui->lineEdit_currentKEY->text() == 0)
    {
        Error_popup err;
        err.set_text("Please select a class or student first.");
        err.exec();
    }

    else{
        ui->lineEdit_KEY->clear();

        setup_rightListWidget("available");

    }

}


/// Associated button
void Manager_GUI::on_pushButton_show_removable_clicked()
{
    ui->pushButton_show_addable->setChecked(0);
    ui->pushButton_show_removable->setChecked(1);
    ui->lineEdit_enterID_inv->clear();
    ui->pushButton_enter2->setDisabled(1);

    if(ui->lineEdit_currentKEY->text() == 0)
    {
        Error_popup err;
        err.set_text("Please select a class or student first.");
        err.exec();
    }

    else{
        ui->lineEdit_KEY->clear();

        setup_rightListWidget("associated");

    }

}


/// Right ListWidget (setup)
void Manager_GUI::setup_rightListWidget(QString kind_of)
{
    ui->listWidget_inv_list->clear();
    ui->listWidget_inv_list->addItems(m_datatservice.get_available_items(kind_of));

}


/// Input by clicking (2nd input)
void Manager_GUI::on_listWidget_inv_list_itemClicked(QListWidgetItem *item)
{
    QString clicked_name = item->text();

    if(!clicked_name.isNull() && m_datatservice.send_second_choice(clicked_name) == true)
    {
        ui->lineEdit_currentVAL->setText(clicked_name);
        ui->lineEdit_enterID_inv->clear();

    }
    else
    {
        Error_popup err;
        err.set_text("Sorry. Rejected request.");
        err.exec();
    }

}


/// Enabling the enter-button
void Manager_GUI::on_lineEdit_enterID_inv_cursorPositionChanged(int arg1, int arg2)
{
    ui->lineEdit_currentVAL->clear();
    ui->pushButton_enter2->setDisabled(0);
}


/// Input by typing (2nd input)
void Manager_GUI::on_pushButton_enter2_clicked()
{
    QString input = ui->lineEdit_enterID_inv->text();
    QString key = ui->lineEdit_currentKEY->text();

    if(     (m_datatservice.send_second_choice(input) == true)
            &&  (           (m_datatservice.get_ID_byName(input) >= 1000
                             && m_datatservice.get_ID_byName(key) < 1000)
                            || (m_datatservice.get_ID_byName(input) < 1000
                                && m_datatservice.get_ID_byName(key) >= 1000)    )
            )
    {
        ui->lineEdit_currentVAL->setText(input);
        ui->lineEdit_enterID_inv->clear();
        ui->listWidget_inv_list->clear();
    }
    else
    {
        Error_popup error;
        error.set_text("Sorry. Rejected request. ID unknown?");
        error.exec();

    }

}


//************************************************* commit buttons (right side)



/// Push_button: join
void Manager_GUI::on_pushButton_join_clicked()
{
    Error_popup mess;

    if(m_datatservice.join_clicked() == true && ui->lineEdit_currentKEY->text() != 0
            && ui->lineEdit_currentVAL->text() != 0)
    {
        ui->lineEdit_currentVAL->clear();
        on_pushButton_show_addable_clicked();
        mess.set_text("Modification cached! Ready for next edit!");
        mess.exec();

    }
    else
    {
        mess.set_text("Modification not possible. Check input.");
        mess.exec();

    }

}


/// Push_button: leave
void Manager_GUI::on_pushButton_leave_clicked()
{
    Error_popup mess;

    if(m_datatservice.leave_clicked() == true && ui->lineEdit_currentKEY->text() != 0
            && ui->lineEdit_currentVAL->text() != 0)
    {
        ui->lineEdit_currentVAL->clear();
        on_pushButton_show_removable_clicked();
        mess.set_text("Modification cached! Ready for next edit!");
        mess.exec();

    }
    else
    {
        mess.set_text("Modification not possible. Check input.");
        mess.exec();

    }

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
