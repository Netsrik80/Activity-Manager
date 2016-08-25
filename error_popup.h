#ifndef ERROR_POPUP_H
#define ERROR_POPUP_H

#include <QDialog>

namespace Ui {
class Error_popup;
}

class Error_popup : public QDialog
{
    Q_OBJECT

public:
    explicit Error_popup(QWidget *parent = 0);
    ~Error_popup();
    void set_text(QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Error_popup *ui;
};

#endif // ERROR_POPUP_H
