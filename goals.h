#ifndef GOALS_H
#define GOALS_H

#include <QMainWindow>
#include <QMessageBox>

#include "databasemanager.h"
#include "mainwindow.h"
#include "usersession.h"

class DatabaseManager;
class MainWindow;

class Goals : public QMainWindow
{
    Q_OBJECT

public:
    explicit Goals(MainWindow* mainWindow, QWidget* parent = nullptr);

    void AddGoal(float amount, QString name);

private:
    DatabaseManager& m_dbManager;
    MainWindow* m_mainWindow;
};

#endif // GOALS_H
