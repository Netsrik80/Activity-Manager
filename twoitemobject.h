#ifndef TWOITEMOBJECT_H
#define TWOITEMOBJECT_H

#include <QString>


class TwoItemObject
{
private:
    int id;
    QString name;

public:
    ///constructors
    TwoItemObject();
    TwoItemObject(int, QString);

    ///set methods
    void set_name(QString);
    void set_id(int); //public?

    ///get methods
    int get_id();
    QString get_name();

};

#endif // TWOITEMOBJECT_H
