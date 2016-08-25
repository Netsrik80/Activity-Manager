#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "studentseditor.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();


private slots:

    void on_pushButton_namesList_clicked();

    void on_pushButton_activityList_clicked();

    void on_pushButton_actManager_clicked();

private:
    Ui::MainMenu *ui;

};

#endif // MAINMENU_H
