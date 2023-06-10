#include "goalswindow.h"
#include "ui_goalswindow.h"

goalsWindow::goalsWindow(Goals *goals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goalsWindow),
    m_goals(goals)
{
    ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

goalsWindow::~goalsWindow()
{
    delete ui;
}

void goalsWindow::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->position().x();
    m_nMouseClick_Y_Coordinate = event->position().y();
}

void goalsWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().x() - m_nMouseClick_X_Coordinate, event->globalPosition().y() - m_nMouseClick_Y_Coordinate);
}

void goalsWindow::show()
{
    if (!isVisible())
    {
        QDialog::show();
    }
}

void goalsWindow::on_submitButton_clicked()
{
    m_goals->AddGoal(ui->amountEdit->value(), ui->nameEdit->text());
    QDialog::close();
}


void goalsWindow::on_closeButton_5_clicked() //zamkniecie ikony dodawana celu
{
    this -> close();
}

