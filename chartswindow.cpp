#include "chartswindow.h"
#include "ui_chartswindow.h"

chartswindow::chartswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chartswindow)
{
    ui->setupUi(this);
}

chartswindow::~chartswindow()
{
    delete ui;
}
