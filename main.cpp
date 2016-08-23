#include "mainmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug("main");
    MainMenu w;
    w.show();

    return a.exec();

}
