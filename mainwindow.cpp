#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>


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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    QPieSeries *series = new QPieSeries();

    series -> append("Transport", 800);
    series -> append("Bills", 60);
    series -> append("Food", 20);
    series -> append("Education", 20);
    series -> append("Health", 60);

    QChart *chart = new QChart();
    chart -> addSeries(series);
    chart -> setTitle("Chart of your expenses");

    QFont titleFont;
    titleFont.setPointSize(25); // Ustawienie rozmiaru na 20
    chart->setTitleFont(titleFont);

    QChartView *chartview = new QChartView(chart);
    chartview -> setParent (ui->horizontalFrame);
    series->setLabelsVisible(true);

    // Ustawienie wyświetlania etykiet procentowych dla każdej części wykresu
    for (QPieSlice *slice : series->slices()) {
        QString label = QString("%1%").arg(100.0 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(QString("%1\n(%2)").arg(slice->label()).arg(label));
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->horizontalFrame);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setMinimumSize(600, 320); // Minimalny rozmiar wykresu

    ui->horizontalFrame->layout()->addWidget(chartView); // Dodanie wykresu do układu

    // Dodatkowo, jeśli korzystasz z okna głównego, możesz ustawić odpowiednią właściwość
    // dla przystosowania wykresu do rozmiaru okna głównego
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    QPieSeries *series2 = new QPieSeries();

    series2 -> append("Transport", 800);
    series2 -> append("Bills", 60);
    series2 -> append("Food", 20);

    QChart *chart2 = new QChart();
    chart2 -> addSeries(series2);
    chart2 -> setTitle("Chart of your incomes");

    QFont titleFont2;
    titleFont2.setPointSize(25); // Ustawienie rozmiaru na 20
    chart2->setTitleFont(titleFont2);

    QChartView *chartview2 = new QChartView(chart2);
    chartview2 -> setParent (ui->horizontalFrame_2);
    series2->setLabelsVisible(true);

    // Ustawienie wyświetlania etykiet procentowych dla każdej części wykresu
    for (QPieSlice *slice : series2->slices()) {
        QString label = QString("%1%").arg(100.0 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(QString("%1\n(%2)").arg(slice->label()).arg(label));
    }

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setParent(ui->horizontalFrame_2);

    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView2->setMinimumSize(600, 310); // Minimalny rozmiar wykresu

    ui->horizontalFrame_2->layout()->addWidget(chartView2); // Dodanie wykresu do układu

    // Dodatkowo, jeśli korzystasz z okna głównego, możesz ustawić odpowiednią właściwość
    // dla przystosowania wykresu do rozmiaru okna głównego
    chartView2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//add new file
void MainWindow::on_signinButton_2_clicked()  //przeniesienie na strone o stronie
{
     QDesktopServices::openUrl(QUrl("http://localhost/financify/financify.php"));
}

//start_page
void MainWindow::on_startButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}
//chart_page
void MainWindow::on_chartButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_closeButton_8_clicked()
{
     this -> close();
}
//from charts_page to home_page
void MainWindow::on_homeButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//user_page
void MainWindow::on_closeButton_10_clicked()
{
    this -> close();
}

void MainWindow::on_accountButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//from charts_page to user_page
void MainWindow::on_accountButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//from user_page to home_page
void MainWindow::on_homeButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//from user_page to chart_page
void MainWindow::on_chartButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}




