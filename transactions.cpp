#include "transactions.h"

Transactions::Transactions(MainWindow* mainWindow, QWidget* parent)
    : QMainWindow(parent)
    , m_dbManager(DatabaseManager::getInstance())
    , m_mainWindow(mainWindow){}

void Transactions::AddTransaction(float amount, QDateTime date, QString type, QString type2)
{
    UserSession& userSession = UserSession::getInstance();
    int userId = userSession.getUserId();

    QString query_prepare = QString("INSERT INTO transactions (user_id, date, type, amount, type2) VALUES ('%1', '%2', '%3', '%4', '%5')")
                                .arg(QString::number(userId), date.toString("yyyy-MM-dd HH:mm"), type, QString::number(amount), type2);

    if (!m_dbManager.executeQuery(query_prepare))
    {
        QMessageBox::about(m_mainWindow, "error", "Something went wrong. Try one more time.");
    }

    if (type == "Income")
        UserSession::getInstance().addIncome(amount);
    else if (type == "Expense")
        UserSession::getInstance().addExpense(amount);

    m_dbManager.GetTotalAmount();
    m_mainWindow->showBalance();
    m_mainWindow->showGoal();
    m_mainWindow->handleFilterChanged();
}
