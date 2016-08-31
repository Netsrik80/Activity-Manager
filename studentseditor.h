#ifndef STUDENTSEDITOR_H
#define STUDENTSEDITOR_H

#include <QDialog>
#include <QString>
#include <QStringListModel>
#include "dataservice.h"

namespace Ui {
class StudentsEditor;
}

class StudentsEditor : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsEditor(QWidget *parent = 0);
    ~StudentsEditor();


private slots:
    void on_QListView_allMembers_clicked(const QModelIndex &index);

    void on_button_add_clicked();

    void on_pushButton_search_clicked();

    void on_button_remove_clicked();

    void on_button_edit_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::StudentsEditor *ui;

    void setupQListView();

    QStringListModel thisModel;

    Dataservice dataRequest; ///only access to data

};

#endif // STUDENTSEDITOR_H
