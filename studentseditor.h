#ifndef STUDENTSEDITOR_H
#define STUDENTSEDITOR_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class StudentsEditor;
}

class StudentsEditor : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsEditor(QWidget *parent = 0);
    ~StudentsEditor();
    QStringListModel thisModel;


private:
    Ui::StudentsEditor *ui;
    void setupQListView();
};

#endif // STUDENTSEDITOR_H
