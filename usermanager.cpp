#include <QCryptographicHash>
#include "usermanager.h"

userManager::userManager()
{
    dbManager = new DatabaseManager();
}

userManager::~userManager()
{

}

void userManager::Login(QString username, QString password)
{
    QByteArray pass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();
    int log = 0;
    index = 0;

    if(dbManager->nextQuery(username, pass, index))
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

void userManager::Registration(QString username, QString password, QString name, QString email)
{
    QByteArray pass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();

    bool check = true;
    index = 1;

    if(!dbManager->nextQuery(username, pass, index))
    {
        check=false;
    }

    if(check)
    {
        QString query_prepare = QString("INSERT INTO users (username, password, name, email) VALUES ('%1', '%2', '%3', '%4')").arg(username, pass, name, email);
        dbManager->executeQuery(query_prepare);
        emit RegisterSuccess(index);
    }
}
