#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QMainWindow>
#include <QDateTime>
#include <QMessageBox>

#include "usersession.h"
#include "databasemanager.h"
#include "mainwindow.h"

class MainWindow;

class Transactions : public QMainWindow
{
    Q_OBJECT
public:
    explicit Transactions(MainWindow* mainWindow, QWidget* parent = nullptr);

    void AddTransaction(float amount, QDateTime date, QString type, QString type2);

private:
    DatabaseManager& m_dbManager;
    MainWindow* m_mainWindow;
};

#endif // TRANSACTIONS_H
