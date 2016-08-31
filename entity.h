#ifndef ENTITY_H
#define ENTITY_H

#include <QList>
#include <QMultiMap>
#include <QMap>
#include <QString>
//#include <manager_dataservice.h>

class Entity
{

private:
    int id;

    QString name;

    QList< int > associates;

    QList< int > candidates;

    bool set_associates(QMultiMap< int, int >);

    bool set_candidates(QMap< int, QString >);

    bool set_name(QMap< int, QString > );


public:
    Entity();

    bool setup(int, QMap< int, QString >, QMap< int, QString > , QMultiMap< int, int > );

    int get_ID();

    QString get_name();

    QList < int > get_associate();

    QList < int > get_candidates();

    bool grab(int);

    bool release(int);

    QMultiMap< int, int > send_your_associates_to(QMultiMap< int, int >);

};

#endif // ENTITY_H
