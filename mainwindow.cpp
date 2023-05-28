#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->showButton->setIcon(QIcon(":/new/prefix1/icons/eye.svg"));
    ui->showButton->setIconSize(QSize(24, 24));
    ui->showButton_2->setIcon(QIcon(":/new/prefix1/icons/eye.svg"));
    ui->showButton_2->setIconSize(QSize(24, 24));

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    m_userManager = new userManager();
    UserSession userSession;

    connect(m_userManager, m_userManager->LoginSuccess, this, &MainWindow::nextWindow);
    connect(m_userManager, m_userManager->RegisterSuccess, this, &MainWindow::nextWindow);

    /*connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton_clicked);
    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::on_signupButton_clicked);
    connect(ui->signinButton, &QPushButton::clicked, this, &MainWindow::on_signinButton_clicked);*/

    //Grupowanie przycisków
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);

    buttonGroup->addButton(ui->homeButton);
    buttonGroup->addButton(ui->settingsButton);
    buttonGroup->addButton(ui->chartButton);
    buttonGroup->addButton(ui->accountButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->position().x();
    m_nMouseClick_Y_Coordinate = event->position().y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().x() - m_nMouseClick_X_Coordinate, event->globalPosition().y() - m_nMouseClick_Y_Coordinate);
}


void MainWindow::on_loginButton_clicked()
{
    QString username = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    m_userManager->Login(username, password);

    ui->passwordEdit->clear();
}

void MainWindow::on_registerButton_clicked()
{
    QString username = ui->loginEdit_2->text();
    QString password = ui->passwordEdit_2->text();
    QString name = ui->nameEdit->text();
    QString email = ui->emailEdit->text();

    m_userManager->Registration(username, password, name, email);
}

void MainWindow::on_signupButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->passwordEdit->clear();
    ui->loginEdit->clear();
}

void MainWindow::on_signinButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->loginEdit_2->clear();
    ui->passwordEdit_2->clear();
    ui->nameEdit->clear();
    ui->emailEdit->clear();
}


void MainWindow::on_showButton_clicked()
{
    if(ui->passwordEdit_2->echoMode() == QLineEdit::Password)
    {
        ui->showButton->setIcon(QIcon(":/new/prefix1/icons/eye-off.svg"));
        ui->passwordEdit_2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->passwordEdit_2->setEchoMode(QLineEdit::Password);
        ui->showButton->setIcon(QIcon(":/new/prefix1/icons/eye.svg"));
    }
}

void MainWindow::on_showButton_2_clicked()
{
    if(ui->passwordEdit->echoMode() == QLineEdit::Password)
    {
        ui->showButton_2->setIcon(QIcon(":/new/prefix1/icons/eye-off.svg"));
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        ui->showButton_2->setIcon(QIcon(":/new/prefix1/icons/eye.svg"));
    }
}


void MainWindow::on_infoButton_clicked()
{
    QMessageBox::about(this, "Information", "The password must be at least 8 characters long, with at least one lowercase letter, one uppercase letter and one number.");
}

void MainWindow::nextWindow(int index)
{
    ui->loginEdit_2->clear();
    ui->passwordEdit_2->clear();
    ui->nameEdit->clear();
    ui->emailEdit->clear();

    ui->passwordEdit->clear();
    ui->loginEdit->clear();

    switch (index)
    {
        case 0:
            ui->stackedWidget->setCurrentIndex(2);
            break;
        case 1:
            ui->stackedWidget->setCurrentIndex(0);
            break;
    }
}

void MainWindow::on_addFundsButton_clicked()
{
    m_transactionsWindow = new transactionsWindow();
    m_transactionsWindow->show();
}


void MainWindow::on_closeButton_clicked()
{
    m_transactionsWindow->reject();
}

