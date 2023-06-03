#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dbManager(DatabaseManager::getInstance())
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

    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setShowGrid(false);

    m_userManager = new userManager();
    m_transactions = new Transactions(this);
    m_goals = new Goals(this);

    connect(m_userManager, m_userManager->LoginSuccess, this, &MainWindow::nextWindow);
    connect(m_userManager, m_userManager->RegisterSuccess, this, &MainWindow::nextWindow);

    connect(ui->filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleFilterChanged(int)));


    /*connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton_clicked);
    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::on_signupButton_clicked);
    connect(ui->signinButton, &QPushButton::clicked, this, &MainWindow::on_signinButton_clicked);*/

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);

    buttonGroup->addButton(ui->homeButton);
    buttonGroup->addButton(ui->settingsButton);
    buttonGroup->addButton(ui->chartButton);
    buttonGroup->addButton(ui->accountButton);
}

MainWindow::~MainWindow()
{
    delete m_userManager;
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
            delete m_userManager;
            ui->stackedWidget->setCurrentIndex(2);
            m_dbManager.GetAmount();
            showBalance();
            showGoal();
            handleFilterChanged(0);
            break;
        case 1:
            ui->stackedWidget->setCurrentIndex(0);
            break;
    }
}

void MainWindow::on_addFundsButton_clicked()
{
    if (!m_transactionsWindow || !m_transactionsWindow->isVisible())
    {
        delete m_transactionsWindow;
        m_transactionsWindow = new transactionsWindow(m_transactions, this);
        m_transactionsWindow->show();
    }
}


void MainWindow::on_closeButton_clicked()
{
    m_transactionsWindow->reject();
}

void MainWindow::showBalance()
{
    ui->income->setText(QString("$")+QString::number(UserSession::getInstance().getTotalIncome()));
    ui->expense->setText(QString("$")+QString::number(UserSession::getInstance().getTotalExpenses()));
    ui->totalBalance->setText(QString("$")+QString::number(UserSession::getInstance().getTotalAmount()));
}

void MainWindow::handleFilterChanged(int index)
{
    QString filterValue = ui->filterComboBox->currentText();

    if (filterValue == "This day")
    {
        QDate currentDate = QDate::currentDate();
        QTime startTime(0, 0);
        QTime endTime(23, 59);

        QDateTime startDateTime(currentDate, startTime);
        QDateTime endDateTime(currentDate, endTime);

        m_dbManager.FetchTransactionsData(ui->tableWidget, startDateTime, endDateTime);
    }

    else if (filterValue == "This week")
    {
        QDate currentDate = QDate::currentDate();
        QDate startDate = currentDate.addDays(-6);
        QTime startTime(0, 0);
        QTime endTime(23, 59);

        QDateTime startDateTime(startDate, startTime);
        QDateTime endDateTime(currentDate, endTime);

        m_dbManager.FetchTransactionsData(ui->tableWidget, startDateTime, endDateTime);
    }

    else if (filterValue == "This month")
    {
        QDate currentDate = QDate::currentDate();
        QDate startDate = currentDate.addDays(-30);
        QTime startTime(0, 0);
        QTime endTime(23, 59);

        QDateTime startDateTime(startDate, startTime);
        QDateTime endDateTime(currentDate, endTime);

        m_dbManager.FetchTransactionsData(ui->tableWidget, startDateTime, endDateTime);
    }

    else if (filterValue == "This year")
    {
        QDate currentDate = QDate::currentDate();
        QDate startDate = currentDate.addDays(-365);
        QTime startTime(0, 0);
        QTime endTime(23, 59);

        QDateTime startDateTime(startDate, startTime);
        QDateTime endDateTime(currentDate, endTime);

        m_dbManager.FetchTransactionsData(ui->tableWidget, startDateTime, endDateTime);
    }

}

void MainWindow::on_addGoalsButton_clicked()
{
    if (!m_goalWindow || !m_goalWindow->isVisible())
    {
        delete m_goalWindow;
        m_goalWindow = new goalsWindow(m_goals, this);
        m_goalWindow->show();
    }
}

void MainWindow::showGoal()
{
    m_dbManager.FetchGoalData(ui->goalName, ui->goalAmount, ui->goalComplete, ui->goalBar);
}

