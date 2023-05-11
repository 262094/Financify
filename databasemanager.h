#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QMessageBox>

class DatabaseManager: public QMainWindow
{
    Q_OBJECT

public:
    DatabaseManager();
    ~DatabaseManager();

    bool executeQuery();
    void Registration(QString username, QString password, QString name, QString email);
    void Login(QString username, QString password);

signals:
    void LoginSuccess(int index);
    void RegisterSuccess(int index);

private:
    QSqlDatabase db;
    int index = 0;
};

#endif // DATABASEMANAGER_H
