#include <QCryptographicHash>
#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    m_databaseReader = new DatabaseReader();

    if (m_databaseReader->readLoginData("db_login.conf"))
    {
        db = QSqlDatabase::addDatabase("QMYSQL", "financify");
        db.setHostName(m_databaseReader->hostname);
        db.setUserName(m_databaseReader->db_username);
        db.setPassword(m_databaseReader->db_password);
        db.setDatabaseName(m_databaseReader->databaseName);
        if (!db.open())
        {
            qDebug() << "Database Error: " << db.lastError().text();
        }
    }
}

DatabaseManager::~DatabaseManager()
{
    QSqlDatabase::database("financify").close();
}

bool DatabaseManager::executeQuery(QString qry)
{
    QSqlQuery query(db);
    query.prepare(qry);

    if (!query.exec())
    {
        qDebug() << "Query Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::nextQuery(QString username, QString password, int index)
{
    QSqlQuery query(db);
    QString query_prepare;

    int user_id = 0;

    switch(index)
    {
        case 0:
            query_prepare = QString("SELECT * FROM users WHERE username = '%1' AND password = '%2'").arg(username, password); //LOGIN
            query.prepare(query_prepare);
            query.exec();

            while(query.next())
            {
                user_id = query.value(0).toInt();
                UserSession& userSession = UserSession::getInstance();
                userSession.setUserId(user_id);
                return true;
            }

            break;

        case 1:
            query_prepare = QString("SELECT * FROM users WHERE username= '%1'").arg(username); //REGISTER
            query.prepare(query_prepare);
            query.exec();

            while(query.next())
            {
                QString usernamedb = query.value(1).toString();
                if (usernamedb == username)
                    return false;
            }
            return true;

            break;
    }

    return 0;
}

void DatabaseManager::GetAmount()
{
    QSqlQuery query(db);
    QString type = "Income";

    UserSession& userSession = UserSession::getInstance();
    query.prepare("SELECT * FROM transactions WHERE user_id = :user_id AND type = :type"); //GETTING Income
    query.bindValue(":id", userSession.getUserId());
    query.bindValue(":type", type);
    if(query.exec() && query.next())
    {
        while(query.next())
        {
            UserSession::getInstance().addIncome(query.value(4).toString());
        }
    }
    else
        qDebug() << "Query Error: " << query.lastError().text();
}
