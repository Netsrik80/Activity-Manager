#include "edit_name.h"
#include "ui_edit_name.h"

Edit_Name::Edit_Name(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit_Name)
{
    ui->setupUi(this);

}


Edit_Name::~Edit_Name()
{
    delete ui;

}

void Edit_Name::on_pushButton_clicked()
{
    get_name();
    this->close();

}

QString Edit_Name::get_name()
{
    return ui->lineEdit->text();

}
