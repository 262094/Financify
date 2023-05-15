#include "databasereader.h"

bool DatabaseReader::readLoginData(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file";
        return false;
    }

    QTextStream in(&file);
    hostname = in.readLine();
    db_username = in.readLine();
    db_password = in.readLine();
    databaseName = in.readLine();
    file.close();

    return true;
}
