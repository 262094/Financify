#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QMainWindow>
#include <QDateTime>
#include <QMessageBox>

#include "usersession.h"
#include "databasemanager.h"


class Transactions : public QMainWindow
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = nullptr);

    void AddTransaction(float amount, QDateTime date, QString type);
    void ShowTransactions();

private:
    DatabaseManager * dbManager;

};

#endif // TRANSACTIONS_H
