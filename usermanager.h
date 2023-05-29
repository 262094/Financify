#ifndef USERMANAGER_H
#define USERMANAGER_H


#include <QMainWindow>
#include <QRegularExpression>
#include <QCryptographicHash>

#include "databasemanager.h"


class userManager : public QMainWindow
{
    Q_OBJECT

public:
    userManager();
    ~userManager();

    bool executeQuery();
    void Registration(QString username, QString password, QString name, QString email);
    void Login(QString username, QString password);

signals:
    void LoginSuccess(int index);
    void RegisterSuccess(int index);

private:
    DatabaseManager& m_dbManager;
    bool isValidEmail(const QString& email);
    bool isValidPassword(const QString& password);

    int index = 0;

};

#endif // USERMANAGER_H
