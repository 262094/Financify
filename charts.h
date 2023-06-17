#ifndef CHARTS_H
#define CHARTS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtCharts>
#include <QFrame>

#include "databasemanager.h"

class DatabaseManager;

class charts : public QMainWindow
{
public:

    explicit charts(QMainWindow *parent = nullptr);
    QChartView *expensesChartView;
    QChartView *incomesChartView;

    void createChart(QFrame *frame1, QFrame *frame2);

private:
    DatabaseManager& m_dbManager;

  bool ChartCreated;

};

#endif // CHARTS_H
