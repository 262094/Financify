#include <QCryptographicHash>

#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("Financify");
    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
    }
}

DatabaseManager::~DatabaseManager() {
    db.close();
}

bool DatabaseManager::executeQuery() {
    QSqlQuery q(db);
    if (!q.exec())
    {
        qDebug() << "Query Error: " << q.lastError().text();
        return false;
    }
    return true;
}

void DatabaseManager::Login(QString username, QString password)
{
    QByteArray pass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", pass);
    executeQuery();

}

void DatabaseManager::Registration(QString username, QString password, QString name, QString surname, QString email)
{

}
