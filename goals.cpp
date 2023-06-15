#include "goals.h"

Goals::Goals(MainWindow* mainWindow, QWidget* parent)
    : QMainWindow(parent)
    , m_dbManager(DatabaseManager::getInstance())
    , m_mainWindow(mainWindow){}

void Goals::AddGoal(float amount, QString name)
{
    UserSession& userSession = UserSession::getInstance();
    int userId = userSession.getUserId();

    if(!m_dbManager.CheckGoalsTable())
    {
        QString query_prepare = QString("INSERT INTO goals (user_id, name, amount) VALUES ('%1', '%2', '%3')")
                                    .arg(QString::number(userId), name, QString::number(amount));

        if (!m_dbManager.executeQuery(query_prepare))
            QMessageBox::about(m_mainWindow, "error", "Something went wrong. Try one more time.");

    }

    else
        QMessageBox::about(this, "error", "You can have only one goal");

    m_mainWindow->showGoal();
}

void Goals::DeleteGoalData()
{
    UserSession& userSession = UserSession::getInstance();
    int userId = userSession.getUserId();

    QString query_prepare = QString("DELETE FROM goals WHERE user_id = '%1'")
                                    .arg(QString::number(userId));

    if (!m_dbManager.executeQuery(query_prepare))
        QMessageBox::about(m_mainWindow, "error", "Something went wrong. Try one more time.");
}




