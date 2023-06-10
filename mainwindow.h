#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QButtonGroup>
#include <QTimer>

#include "usermanager.h"
#include "databasemanager.h"
#include "transactionsWindow.h"
#include "transactions.h"
#include "goalswindow.h"
#include "goals.h"

class Transactions;
class transactionsWindow;
class Goals;
class goalsWindow;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showBalance();
    void showGoal();

private:
    Ui::MainWindow *ui;

    userManager* m_userManager{nullptr};

    transactionsWindow * m_transactionsWindow{nullptr};
    Transactions* m_transactions{nullptr};

    DatabaseManager& m_dbManager;

    goalsWindow* m_goalWindow{nullptr};
    Goals* m_goals{nullptr};

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void nextWindow(int);
    void handleFilterChanged(int index);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_signupButton_clicked();
    void on_signinButton_clicked();
    void on_showButton_clicked();
    void on_infoButton_clicked();
    void on_showButton_2_clicked();
    void on_addFundsButton_clicked();
    void on_closeButton_clicked();
    void on_addGoalsButton_clicked();
    void on_signinButton_2_clicked();
    void on_startButton_clicked();
    void on_chartButton_clicked();
    void on_closeButton_8_clicked();
    void on_homeButton_3_clicked();
};
#endif // MAINWINDOW_H
