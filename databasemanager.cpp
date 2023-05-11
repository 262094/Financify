#include <QCryptographicHash>
#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "financify");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("financify");
    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
    }
}

DatabaseManager::~DatabaseManager()
{
    QSqlDatabase::database("financify").close();
    QSqlDatabase::removeDatabase("financify");
}

bool DatabaseManager::executeQuery()
{
    QSqlQuery query(db);
    if (!query.exec())
    {
        qDebug() << "Query Error: " << query.lastError().text();
        return false;
    }
    return true;
}

void DatabaseManager::Login(QString username, QString password)
{
    QByteArray pass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();
    int log = 0;
    index = 2;

    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", pass);

    if(query.exec() && query.next())
    {
        log++;
    }

    switch (log)
    {
        case 0:
            QMessageBox::about(this, "error", "Your login or password is not correct");
            break;
        case 1:
            emit LoginSuccess(index);
            break;
    }
}

void DatabaseManager::Registration(QString username, QString password, QString name, QString email)
{
    QSqlQuery query(db);
    bool check=true;
    index = 0;

    query.prepare("select * from users where username=:username");
    query.bindValue(":username", username);

    QByteArray pass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();

    query.exec();

    while(query.next())
    {
        QString usernamedb = query.value(1).toString();
        if(username == usernamedb)
        {
            check=false;
        }
    }

    if(check)
    {
        query.prepare("insert into users (username, password, name, email)" "VALUES (:username, :password, :name, :email)");
        query.bindValue(":username", username);
        query.bindValue(":password", pass);
        query.bindValue(":name", name);
        query.bindValue(":email", email);
        query.exec();
        emit RegisterSuccess(index);
    }
}
