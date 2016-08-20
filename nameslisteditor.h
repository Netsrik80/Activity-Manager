#ifndef NAMESLISTEDITOR_H
#define NAMESLISTEDITOR_H

#include <QDialog>

namespace Ui {
class NameslistEditor;
}

class NameslistEditor : public QDialog
{
    Q_OBJECT

public:
    explicit NameslistEditor(QWidget *parent = 0);
    ~NameslistEditor();

private:
    Ui::NameslistEditor *ui;
};

#endif // NAMESLISTEDITOR_H
