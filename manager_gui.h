#ifndef MANAGER_GUI_H
#define MANAGER_GUI_H

#include <QDialog>
#include "manager_dataservice.h"
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

    void on_pushButton_save_clicked();

    void on_pushButton_enter_clicked();

    void on_pushButton_add_to_clicked();

    void on_lineEdit_enterID_cursorPositionChanged(int arg1, int arg2);


    void on_listWidget_inv_list_itemClicked(QListWidgetItem *item);

    void on_pushButton_enter_inv_clicked();

    void on_pushButton_remove_clicked();

    void on_lineEdit_enterID_inv_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_exit_clicked();

private:
    Ui::Manager_GUI *ui;

    ///Setup of the dataservice for the session
    Manager_Dataservice m_datatservice;

    void setup_leftListWidget();

    void setup_rightListWidget();

    ///1=students, 2=activities
    int mode;

    void view_status(int);

};

#endif // MANAGER_GUI_H
