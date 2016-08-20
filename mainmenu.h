#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

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
    void on_pushButton_liste_1_clicked();

    void on_pushButton_liste_2_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H