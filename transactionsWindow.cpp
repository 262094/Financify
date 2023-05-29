#include <QMouseEvent>

#include "transactionsWindow.h"
#include "ui_transactionsWindow.h"

transactionsWindow::transactionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transactionsWindow)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
}

transactionsWindow::~transactionsWindow()
{
    delete ui;
}

void transactionsWindow::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->position().x();
    m_nMouseClick_Y_Coordinate = event->position().y();
}

void transactionsWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().x() - m_nMouseClick_X_Coordinate, event->globalPosition().y() - m_nMouseClick_Y_Coordinate);
}


void transactionsWindow::on_submitButton_clicked()
{
    m_transactions = new Transactions();
    m_transactions->AddTransaction(ui->amountEdit->value(), ui->dateEdit->dateTime(), ui->typeEdit->currentText());
}

void transactionsWindow::show()
{
    if (!isVisible())
    {
        QDialog::show();
    }
}

