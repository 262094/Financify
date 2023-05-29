#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QMessageBox>
#include <QCryptographicHash>

#include "databasereader.h"
#include "usersession.h"

class DatabaseManager
{

public:
    static DatabaseManager& getInstance();

    DatabaseManager();
    ~DatabaseManager();

    bool executeQuery(QString qry);
    bool nextQuery(QString username, QString password, int Index);
    void GetAmount();

private:
    QSqlDatabase db;
    DatabaseReader * m_databaseReader{nullptr};
    UserSession userSession;

};

#endif // DATABASEMANAGER_H
