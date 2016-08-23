#ifndef EDIT_NAME_H
#define EDIT_NAME_H

#include <QDialog>

namespace Ui {
class Edit_Name;
}

class Edit_Name : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_Name(QWidget *parent = 0);
    ~Edit_Name();
    QString get_name();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Edit_Name *ui;

};

#endif // EDIT_NAME_H
