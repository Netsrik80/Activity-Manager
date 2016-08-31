#ifndef TWOITEMOBJECT_H
#define TWOITEMOBJECT_H

#include <QString>

class TwoItemObject
{
private:
    ///private member variables
    int id;
    int id2;
    QString name;

public:
    ///constructors
    TwoItemObject();

    TwoItemObject(int, QString);

    TwoItemObject(int, int);

    /// get & set
    void set_id(int);

    int get_id();

    void set_id2(int);

    int get_id2();

    void set_name(QString);

    QString get_name();

};

#endif // TWOITEMOBJECT_H
