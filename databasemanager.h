#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QMessageBox>

#include "databasereader.h"

class DatabaseManager: public QMainWindow
{
    Q_OBJECT

public:
    DatabaseManager();
    ~DatabaseManager();

    bool executeQuery(QString qry);
    bool nextQuery(QString username, QString password, int Index);

private:
    QSqlDatabase db;
    DatabaseReader * m_databaseReader;
};

#endif // DATABASEMANAGER_H
