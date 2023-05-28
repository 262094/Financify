#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QButtonGroup>

#include "usermanager.h"
#include "transactionsWindow.h"
#include "databasemanager.h"
#include "transactions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    userManager * m_userManager;
    transactionsWindow * m_transactionsWindow;

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void nextWindow(int);

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
};
#endif // MAINWINDOW_H
