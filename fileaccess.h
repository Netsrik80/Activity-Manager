#ifndef FILEACCESS_H
#define FILEACCESS_H

#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QTextStream>
#include <QVector>
#include <QVariant>
#include <QStringList>
#include <QList>


class FileAccess : public QObject
{
    Q_OBJECT
public:
    explicit FileAccess(QObject *parent = 0);

signals:

public slots:
};

#endif // FILEACCESS_H
