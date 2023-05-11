#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>

class DatabaseManager: public QMainWindow
{
    Q_OBJECT

public:
    DatabaseManager();
    ~DatabaseManager();

    bool executeQuery();
    void Registration(QString username, QString password, QString name, QString email);
    void Login(QString username, QString password);

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
