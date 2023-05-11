#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    DatabaseManager * dbManager = new DatabaseManager();
    QString username = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    dbManager->Login(username, password);
    dbManager->~DatabaseManager();
}

void MainWindow::on_registerButton_clicked()
{
    DatabaseManager * dbManager = new DatabaseManager();
    QString username = ui->loginEdit_2->text();
    QString password = ui->passwordEdit_2->text();
    QString name = ui->nameEdit->text();
    QString email = ui->emailEdit->text();

    dbManager->Registration(username, password, name, email);
    dbManager->~DatabaseManager();
}
