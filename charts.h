#ifndef CHARTS_H
#define CHARTS_H

#include <QMainWindow>
#include <QtCharts>
#include <QFrame>

#include "databasemanager.h"

class DatabaseManager;

class charts : public QMainWindow
{
public:
    charts();

    QChartView *expensesChartView;
    QChartView *incomesChartView;

    void createChart(QFrame *frame1, QFrame *frame2);
    void destroyChart();

private:
    DatabaseManager& m_dbManager;

    void destroySeries(QPieSeries* series, QChart* chart, QChartView* chartView);

    bool ChartCreated;

    QPieSeries * series;
    QPieSeries *series2;

    QChart *chart;
    QChart *chart2;

    QChartView *chartview;
    QChartView *chartview2;
};

#endif // CHARTS_H
