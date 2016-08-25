#ifndef MANAGER_GUI_H
#define MANAGER_GUI_H

#include <QDialog>
#include "manager_data_admin.h"
#include <QListWidgetItem>

namespace Ui {
class Manager_GUI;
}

class Manager_GUI : public QDialog
{
    Q_OBJECT

public:
    explicit Manager_GUI(QWidget *parent = 0);
    ~Manager_GUI();

private slots:
    void on_listWidget_list_itemClicked(QListWidgetItem *item);

    void on_pushButton_students_clicked();

    void on_pushButton_classes_clicked();

    void on_pushButton_save_2_clicked();

    void on_pushButton_enter_clicked();

private:
    Ui::Manager_GUI *ui;
    void setup_listWidget(int);
    Manager_Data_Admin data_admin;
    int mode; ///1=student, 2=activities
    int invert_mode(int, int);
};

#endif // MANAGER_GUI_H
