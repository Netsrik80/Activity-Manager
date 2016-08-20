#include "nameslisteditor.h"
#include "ui_nameslisteditor.h"

NameslistEditor::NameslistEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameslistEditor)
{
    ui->setupUi(this);
}

NameslistEditor::~NameslistEditor()
{
    delete ui;
}
