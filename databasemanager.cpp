#include "databasemanager.h"

DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager()
{
    m_databaseReader = new DatabaseReader();

    if (QSqlDatabase::contains("financify"))
    {
        QSqlDatabase::database("financify").close();
        QSqlDatabase::removeDatabase("financify");
    }

    if (m_databaseReader->readLoginData("db_login.ini"))
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
    QString type1 = "Expense";

    UserSession& userSession = UserSession::getInstance();

    QDateTime currentDate = QDateTime::currentDateTime();

    query.prepare("SELECT * FROM transactions WHERE user_id = :user_id AND type = :type"); //GETTING Income
    query.bindValue(":user_id", userSession.getUserId());
    query.bindValue(":type", type);
    if(query.exec())
    {
        while(query.next())
        {
            QDateTime transactionDate = query.value(2).toDateTime();
            if (transactionDate.date() == currentDate.date())
            {
                UserSession::getInstance().addIncome(query.value(4).toFloat());
            }
        }
    }
    else
            qDebug() << "Query Error: " << query.lastError().text();

    query.prepare("SELECT * FROM transactions WHERE user_id = :user_id AND type = :type");
    query.bindValue(":user_id", userSession.getUserId());
    query.bindValue(":type", type1);
    if(query.exec())
    {
        while(query.next())
        {
            QDateTime transactionDate = query.value(2).toDateTime();

            if (transactionDate.date() == currentDate.date())
            {
                UserSession::getInstance().addExpense(query.value(4).toFloat());
            }
        }
    }
    else
        qDebug() << "Query Error: " << query.lastError().text();

    GetTotalAmount();
}

void DatabaseManager::GetTotalAmount()
{
    UserSession& userSession = UserSession::getInstance();
    int userId = userSession.getUserId();

    QSqlQuery query(db);
    QString type = "Income";
    QString type1 = "Expense";

    float totalIncome = 0;
    float totalExpense = 0;

    query.prepare("SELECT SUM(amount) FROM transactions WHERE user_id = :user_id AND type = :type");
    query.bindValue(":user_id", userId);
    query.bindValue(":type", type);
    if (query.exec() && query.next())
    {
        totalIncome = query.value(0).toFloat();

    }
    else
    {
        qDebug() << "Query Error: " << query.lastError().text();
        return;
    }

    query.prepare("SELECT SUM(amount) FROM transactions WHERE user_id = :user_id AND type = :type");
    query.bindValue(":user_id", userId);
    query.bindValue(":type", type1);
    if (query.exec() && query.next())
    {
        totalExpense = query.value(0).toFloat();
    }
    else
    {
        qDebug() << "Query Error: " << query.lastError().text();
        return;
    }

    float totalBudget = totalIncome - totalExpense;
    userSession.setTotalAmount(totalBudget);
}

void DatabaseManager::FetchAllData(QTableWidget* tableWidget, const QDateTime& startDateTime, const QDateTime& endDateTime)
{
    tableWidget->clear();
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    QSqlQuery query(db);
    query.prepare("SELECT date, type, amount FROM transactions WHERE user_id = :user_id AND date BETWEEN :start_date AND :end_date");
    query.bindValue(":user_id", UserSession::getInstance().getUserId());
    query.bindValue(":start_date", startDateTime.toString("yyyy-MM-dd HH:mm"));
    query.bindValue(":end_date", endDateTime.toString("yyyy-MM-dd HH:mm"));

    if (query.exec())
    {
        tableWidget->setColumnCount(3);
        tableWidget->setSortingEnabled(false);
        tableWidget->setUpdatesEnabled(false);

        int row = 0;

        while (query.next())
        {
            QDate date = query.value(0).toDate();
            QString type = query.value(1).toString();
            float amount = query.value(2).toFloat();

            QTableWidgetItem* itemDate = new QTableWidgetItem(date.toString("yyyy-MM-dd"));
            QTableWidgetItem* itemType = new QTableWidgetItem(type);
            QTableWidgetItem* itemAmount = new QTableWidgetItem(QString::number(amount));

            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, itemDate);
            tableWidget->setItem(row, 1, itemType);
            tableWidget->setItem(row, 2, itemAmount);

            row++;
        }

        tableWidget->setSortingEnabled(true);
        tableWidget->setUpdatesEnabled(true);
        tableWidget->resizeColumnsToContents();
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    else
    {
        qDebug() << "Query Error: " << query.lastError().text();
    }
}

