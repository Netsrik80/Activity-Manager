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

    ///set methods
    void set_name(QString);
    void set_id(int);
    void set_id2(int);

    ///get methods
    int get_id();
    int get_id2();
    QString get_name();

};

#endif // TWOITEMOBJECT_H
