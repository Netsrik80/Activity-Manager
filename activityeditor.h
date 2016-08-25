#ifndef ACTIVITYEDITOR_H
#define ACTIVITYEDITOR_H

#include <QDialog>
#include "dataservice.h"
#include <QStringListModel>

namespace Ui {
class ActivityEditor;
}

class ActivityEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ActivityEditor(QWidget *parent = 0);
    ~ActivityEditor();

private slots:
    void on_QListView_allMembers_clicked(const QModelIndex &index);

    void on_button_add_clicked();

    void on_pushButton_search_clicked();

    void on_button_remove_clicked();

    void on_button_edit_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::ActivityEditor *ui;
    void setupQListView();
    QStringListModel thisModel;
    Dataservice dataRequest; ///only access to data
};

#endif // ACTIVITYEDITOR_H
