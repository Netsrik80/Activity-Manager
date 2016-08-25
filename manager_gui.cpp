#include "manager_gui.h"
#include "ui_manager_gui.h"
#include <QListWidget>
#include <QListWidgetItem>


Manager_GUI::Manager_GUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager_GUI)
{
    ui->setupUi(this);
    //setup_listWidget();
    ui->pushButton_enter->setDisabled(1);
}

Manager_GUI::~Manager_GUI()
{
    delete ui;
}


void Manager_GUI::setup_listWidget(int case_nmbr)
{
    ui->listWidget_list->clear();
    ui->listWidget_inv_list->clear();
    ui->lineEdit_enterID->clear();
    ui->lineEdit_search->clear();
    ui->pushButton_enter->setDisabled(1);
    qDebug("setupList");
    QStringList items;
    QStringList inv_items;
    switch (case_nmbr) {
    case 1:
        items = data_admin.get_studentslist();
        ui->listWidget_list->addItems( items );
        inv_items = data_admin.get_activitieslist();
        ui->listWidget_inv_list->addItems(inv_items);
        break;

    case 2:
        items = data_admin.get_activitieslist();
        ui->listWidget_list->addItems( items );
        inv_items = data_admin.get_studentslist();
        ui->listWidget_inv_list->addItems(inv_items);
        break;
    default:
        ui->listWidget_list->addItem("no list available");
        break;
    }


}


void Manager_GUI::on_listWidget_list_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_search->setDisabled(1);
    QString clicked_name = item->text();
    QVariant id = data_admin.get_id_byName(mode, clicked_name);
    ui->lineEdit_search->setText(clicked_name);
    if(id != 1) {ui->lineEdit_enterID->setText(id.toString());}
    ui->pushButton_enter->setEnabled(1);

}

void Manager_GUI::on_pushButton_students_clicked()
{

    mode = 1;
    setup_listWidget(mode);

}

void Manager_GUI::on_pushButton_classes_clicked()
{

    mode = 2;
    setup_listWidget(mode);
}

void Manager_GUI::on_pushButton_save_2_clicked()
{
    this->close();
}

int Manager_GUI::invert_mode(int mode, int)
{
    if(mode == 1){return 2;}
    if(mode == 2) {return 1;}
    qDebug("mode error");
    return 0;
}

void Manager_GUI::on_pushButton_enter_clicked()
{
    QVariant read_ID = ui->lineEdit_enterID->text();
    data_admin.set_key_id_toEdit(mode, read_ID.toInt());


}
