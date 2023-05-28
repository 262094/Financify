#include "transactions.h"
#include "databasemanager.h"

Transactions::Transactions(QWidget *parent)
    : QMainWindow{parent}
{
    dbManager = new DatabaseManager();
}

void Transactions::AddTransaction(float amount, QDateTime date, QString type)
{
    UserSession& userSession = UserSession::getInstance();
    int userId = userSession.getUserId();

    QString query_prepare = QString("INSERT INTO transactions (user_id, date, type, amount) VALUES ('%1', '%2', '%3', '%4')")
                                .arg(QString::number(userId), date.toString("yyyy-MM-dd HH:mm"), type, QString::number(amount));

    if(!dbManager->executeQuery(query_prepare))
        QMessageBox::about(this, "error", "Something went wrong. Try one more time.");

    dbManager->GetAmount();
}
