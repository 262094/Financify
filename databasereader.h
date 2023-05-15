#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include <QDebug>
#include <QFile>
#include <QTextStream>

class DatabaseReader
{

public:
    bool readLoginData(const QString& fileName);

    QString hostname;
    QString db_username;
    QString db_password;
    QString databaseName;
};

#endif // DATABASEREADER_H
