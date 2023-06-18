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

void DatabaseManager::FetchTransactionsData(QTableWidget* tableWidget, const QDateTime& startDateTime, const QDateTime& endDateTime)
{
    tableWidget->clear();
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    QSqlQuery query(db);
    query.prepare("SELECT date, type, amount, type2 FROM transactions WHERE user_id = :user_id AND date BETWEEN :start_date AND :end_date");
    query.bindValue(":user_id", UserSession::getInstance().getUserId());
    query.bindValue(":start_date", startDateTime.toString("yyyy-MM-dd HH:mm"));
    query.bindValue(":end_date", endDateTime.toString("yyyy-MM-dd HH:mm"));

    if (query.exec())
    {
        tableWidget->setColumnCount(4);
        tableWidget->setSortingEnabled(false);
        tableWidget->setUpdatesEnabled(false);

        int row = 0;

        while (query.next())
        {
            QDate date = query.value(0).toDate();
            QString type = query.value(1).toString();
            float amount = query.value(2).toFloat();
            QString type2 = query.value(3).toString();

            QTableWidgetItem* itemDate = new QTableWidgetItem(date.toString("yyyy-MM-dd"));
            QTableWidgetItem* itemType = new QTableWidgetItem(type);
            QTableWidgetItem* itemAmount = new QTableWidgetItem(QString("$")+QString::number(amount));
            QTableWidgetItem* itemType2 = new QTableWidgetItem(type2);

            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, itemDate);
            tableWidget->setItem(row, 1, itemType);
            tableWidget->setItem(row, 2, itemAmount);
            tableWidget->setItem(row, 3, itemType2);

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

bool DatabaseManager::CheckGoalsTable()
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM goals WHERE user_id = :user_id");
    query.bindValue(":user_id", UserSession::getInstance().getUserId());

    if (query.exec() && query.next())
    {
        int rowCount = query.value(0).toInt();
        if (rowCount > 0)
            return true;
        else
            return false;
    }

    else
        qDebug() << "Query Error: " << query.lastError().text();

    return 0;

}

void DatabaseManager::chartView(QPieSeries* series, QPieSeries* series2)
{

    float transportexpense = 0;
    float billsexpense = 0;
    float foodexpense = 0;
    float healthexpense = 0;
    float educationexpense = 0;

    float transportincome = 0;
    float billsincome = 0;
    float foodincome = 0;
    float healthincome = 0;
    float educationincome = 0;

    QSqlQuery query(db);
    query.prepare("SELECT type, amount, type2 FROM transactions WHERE user_id = :user_id");
    query.bindValue(":user_id", UserSession::getInstance().getUserId());

    if (query.exec())
    {
        while (query.next())
        {
            QString type = query.value(0).toString();
            float amount = query.value(1).toFloat();
            QString type2 = query.value(2).toString();

            if (type == "Income")
            {
                if (type2 == "Transport")
                    transportincome += amount;
                else if (type2 == "Bills")
                    billsincome += amount;
                else if (type2 == "Food")
                    foodincome += amount;
                else if (type2 == "Health")
                    healthincome += amount;
                else if (type2 == "Education")
                    educationincome += amount;
            }
            else if (type == "Expense")
            {
                if (type2 == "Transport")
                    transportexpense += amount;
                else if (type2 == "Bills")
                    billsexpense += amount;
                else if (type2 == "Food")
                    foodexpense += amount;
                else if (type2 == "Health")
                    healthexpense += amount;
                else if (type2 == "Education")
                    educationexpense += amount;
            }
        }
    }
    else
    {
        qDebug() << "Query Error: " << query.lastError().text();
    }

    series->append("Transport", transportincome)->setBrush(QColor("#FF0000"));
    series->append("Bills", billsincome)->setBrush(QColor("#00FF00"));
    series->append("Food", foodincome)->setBrush(QColor("#0000FF"));
    series->append("Health", healthincome)->setBrush(QColor("#FFFF00"));
    series->append("Education", educationincome)->setBrush(QColor("#FF00FF"));

    series2->append("Transport", transportexpense)->setBrush(QColor("#FF0000"));
    series2->append("Bills", billsexpense)->setBrush(QColor("#00FF00"));
    series2->append("Food", foodexpense)->setBrush(QColor("#0000FF"));
    series2->append("Health", healthexpense)->setBrush(QColor("#FFFF00"));
    series2->append("Education", educationexpense)->setBrush(QColor("#FF00FF"));

}




void DatabaseManager::FetchGoalData(QLabel* goalNameLabel, QLabel* goalAmountLabel, QPushButton* completeButton, QProgressBar* progressBar)
{
    QSqlQuery query(db);
    query.prepare("SELECT name, amount FROM goals WHERE user_id = :user_id");
    query.bindValue(":user_id", UserSession::getInstance().getUserId());

    QString name;
    float amount = 0.0f;
    float totalAmount = UserSession::getInstance().getTotalAmount();

    if (query.exec())
    {
        while (query.next())
        {
            name = query.value(0).toString();
            amount = query.value(1).toFloat();
        }
    }

    else
    {
        qDebug() << "Query Error: " << query.lastError().text();
    }

    if(CheckGoalsTable())
    {
        goalNameLabel->setText(name);

        if (amount <= totalAmount)
        {
            goalAmountLabel->setText("$" + QString::number(amount));
        }
        else
            goalAmountLabel->setText("$" + QString::number(totalAmount));

        int value = totalAmount/amount * 100;
        if (value >= 100)
        {
            completeButton->show();
            value = 100;
        }
        else
            completeButton->hide();

        progressBar->setValue(value);
    }
    else
    {
        goalNameLabel->setText("");
        goalAmountLabel->setText("");
        progressBar->setValue(0);
        completeButton->hide();
    }

}

