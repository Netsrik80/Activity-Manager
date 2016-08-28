/**
  * Dialog for messages for the user (not only errors)
  */

#include "error_popup.h"
#include "ui_error_popup.h"

Error_popup::Error_popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Error_popup)
{
    ui->setupUi(this);
}

Error_popup::~Error_popup()
{
    delete ui;
}

void Error_popup::set_text(QString text)
{
    ui->label->setText(text);
}

void Error_popup::on_pushButton_clicked()
{
    this->close();
}
