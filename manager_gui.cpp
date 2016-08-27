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
    mode = 1; //initial value = students
    view_status(1);

}


Manager_GUI::~Manager_GUI()
{
    delete ui;
}

/****************
 *              *
 *  Buttons     *
 *              *
 * *************/


///Button: Students
void Manager_GUI::on_pushButton_students_clicked()
{
    qDebug("ui clicked students");
    mode = 1;
    m_datatservice.set_guiMode("students");
    setup_leftListWidget();
    view_status(2);

}


///Button: Classes
void Manager_GUI::on_pushButton_classes_clicked()
{
    qDebug("ui clicked classes");
    mode = 2;
    m_datatservice.set_guiMode("activities");
    setup_leftListWidget();
    view_status(2);
}


///Button: Enter
void Manager_GUI::on_pushButton_enter_clicked()
{
    qDebug("ui clicked enter");

    QVariant req_ID = ui->lineEdit_enterID->text();
    if(m_datatservice.check_ID(req_ID.toInt()) == true)
    {
        ///Just for testing (if name would change again, there would be a problem)
        ui->lineEdit_search->setText(m_datatservice.get_Name_byID(req_ID.toInt()));

        ///sends the id (student/activity) and sets the corresponding combi-list (mmap) to active
        m_datatservice.send_ID_toEdit(req_ID.toInt());
        ui->pushButton_add_to->setDisabled(0);
        ui->pushButton_remove->setDisabled(0);
        qDebug("id committed to, mmap set in man_dataserv");
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
    ui->label_choosen->setText(ui->lineEdit_search->text());
    qDebug("clicked add button");
    ui->listWidget_inv_list->clear();
    m_datatservice.set_editMode("add");
    setup_rightListWidget();
    ui->pushButton_enter_inv->setText("add to");

}

/// Remove Button
void Manager_GUI::on_pushButton_remove_clicked()
{
    qDebug("clicked add button");
    ui->listWidget_inv_list->clear();
    m_datatservice.set_editMode("remove");
    setup_rightListWidget();
    ui->pushButton_enter_inv->setText("remove from");
}


///Edit Button
void Manager_GUI::on_pushButton_enter_inv_clicked()
{
    qDebug("ui clicked edit button");

    QVariant req_ID = ui->lineEdit_enterID_inv->text();

    if(m_datatservice.check_ID(req_ID.toInt()) == true)
    {
        m_datatservice.do_edit_with(req_ID.toInt());

        ui->lineEdit_enterID_inv->clear();
        ui->lineEdit_search_inv->clear();

        Error_popup message;
        message.set_text("Edit succeed.");
        message.exec();
    }

    else{
        Error_popup error;
        error.set_text("ID unknown");
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

/****************
 *              *
 * ListWidgets  *
 *              *
 * *************/

///Left ListWidget (view)
void Manager_GUI::setup_leftListWidget()
{         
     qDebug("ui setup left list widget");
    ui->listWidget_list->clear();
    switch (mode) {

    case 1:
        ui->listWidget_list->clear();
        ui->listWidget_list->addItems(m_datatservice.get_all_names(mode));
        ui->label->setText("Name: ");
        ui->label_8->setText("Activity: ");
        break;

    case 2:
        ui->listWidget_list->clear();
        ui->listWidget_list->addItems(m_datatservice.get_all_names(mode));
        ui->label_8->setText("Name: ");
        ui->label->setText("Activity: ");
        break;

    default:
        ui->listWidget_list->addItem("no list available");
        qDebug("gui_manager setup_list_widget returns error");
        break;
    }

}


///Left ListWidget (action)
void Manager_GUI::on_listWidget_list_itemClicked(QListWidgetItem *item)
{
    qDebug("ui clicked on an item");
    view_status(2);
    QString clicked_name = item->text();
    QVariant id = m_datatservice.get_ID_byName("leftWidget", clicked_name);
    m_datatservice.set_editMode("remove");
    m_datatservice.send_ID_toEdit(id.toInt());
    setup_rightListWidget();
    ui->lineEdit_search->setText(clicked_name);
    ui->lineEdit_enterID->setText(id.toString());

}

///Right ListWidget
void Manager_GUI::setup_rightListWidget()
{
    qDebug("ui setup_rightListWidget");
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
    /// not mode is active !!!!!!!!!!!! m_datatservice.se
}



/****************
 *              *
 * Input fields *
 *              *
 * *************/

/// Left id-input-field (action)
void Manager_GUI::on_lineEdit_enterID_cursorPositionChanged(int arg1, int arg2)
{
    ui->listWidget_list->setCurrentRow(-1);

}

/// Right id-input-field (action)
void Manager_GUI::on_lineEdit_enterID_inv_cursorPositionChanged(int arg1, int arg2)
{
    ui->listWidget_inv_list->setCurrentRow(-1);
}



/****************
 *              *
 * View modes   *
 *              *
 * *************/

void Manager_GUI::view_status(int status)
{
    switch (status) {
    ///Start
    case 1:
       setup_leftListWidget();
        break;
    ///Pressed "students" or "classes"
    case 2:
        /*ui->pushButton_enter->setDisabled(0);
        ui->pushButton_add_to->setDisabled(1);
        ui->pushButton_enter_inv->setDisabled(1);
        ui->pushButton_remove->setDisabled(1);
        ui->pushButton_search->setDisabled(1);
        ui->pushButton_search_inv->setDisabled(1);

        ui->lineEdit_enterID_inv->clear();
        ui->lineEdit_enterID_inv->setDisabled(1);
        ui->lineEdit_enterID->clear();
        ui->lineEdit_enterID->setDisabled(0);
        ui->lineEdit_search->setDisabled(1);
        ui->lineEdit_search_inv->clear();
        ui->lineEdit_search_inv->setReadOnly(1);

        ui->listWidget_inv_list->clear();
        //ui->listWidget_list->clear();*/
        break;
    case 3:

        break;
    case 4:

        break;
    default:
        break;
    }

}





