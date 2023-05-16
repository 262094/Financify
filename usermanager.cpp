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
        bool isEmailValid = isValidEmail(email);
        bool isPasswordValid = isValidPassword(password);

        if(isEmailValid && isPasswordValid)
        {
            QString query_prepare = QString("INSERT INTO users (username, password, name, email) VALUES ('%1', '%2', '%3', '%4')").arg(username, pass, name, email);
            if(dbManager->executeQuery(query_prepare))
                emit RegisterSuccess(index);
            else
                QMessageBox::about(this, "error", "Something went wrong. Try one more time.");
        }
        else if(!isEmailValid && !isPasswordValid)
            QMessageBox::about(this, "error", "Email and password are invalid.");
        else if(isEmailValid && !isPasswordValid)
            QMessageBox::about(this, "error", "Password is invalid.");
        else if(!isEmailValid && isPasswordValid)
            QMessageBox::about(this, "error", "Email is invalid.");
    }
}

bool userManager::isValidEmail(const QString& email)
{
    static QRegularExpression emailRegex("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    return emailRegex.match(email).hasMatch();
}

bool userManager::isValidPassword(const QString& password) {
    static QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    return passwordRegex.match(password).hasMatch();
}
