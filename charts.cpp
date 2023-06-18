#include "charts.h"


charts::charts() : m_dbManager(DatabaseManager::getInstance())
{
    series = new QPieSeries();
    chart = new QChart();

    series2 = new QPieSeries();
    chart2 = new QChart();

    chartview = new QChartView(chart);
    chartview2 = new QChartView(chart2);
}

void charts::createChart(QFrame *frame1, QFrame *frame2)
{
    if (series)
    {
        destroySeries(series, chart, chartview);
    }

    if (series2)
    {
        destroySeries(series2, chart2, chartview2);
    }

    series = new QPieSeries();
    chart = new QChart();
    chartview = new QChartView(chart);

    series2 = new QPieSeries();
    chart2 = new QChart();
    chartview2 = new QChartView(chart2);

    m_dbManager.chartView(series, series2);

    chart->addSeries(series);
    chart->setTitle("Chart of your income");
    QFont titleFont;
    titleFont.setPointSize(20);
    chart->setTitleFont(titleFont);
    chartview->setParent(frame1);
    series->setLabelsVisible(true);

    for (QPieSlice *slice : series->slices()) {
        QString label = QString("%1%").arg(100.0 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(QString("%1\n(%2)").arg(slice->label()).arg(label));
    }

    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartview->setMinimumSize(600, 320);
    frame1->layout()->addWidget(chartview);
    chartview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    chart2->addSeries(series2);
    chart2->setTitle("Chart of your expenses");
    QFont titleFont2;
    titleFont2.setPointSize(20);
    chart2->setTitleFont(titleFont2);
    chartview2->setParent(frame2);
    series2->setLabelsVisible(true);

    for (QPieSlice *slice : series2->slices()) {
        QString label = QString("%1%").arg(100.0 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(QString("%1\n(%2)").arg(slice->label()).arg(label));
    }

    chartview2->setRenderHint(QPainter::Antialiasing);
    chartview2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartview2->setMinimumSize(600, 310);
    frame2->layout()->addWidget(chartview2);
    chartview2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void charts::destroyChart()
{
    chartview->setParent(nullptr);
    chartview2->setParent(nullptr);

    destroySeries(series, chart, chartview);
    destroySeries(series2, chart2, chartview2);

    chartview = nullptr;
    chart = nullptr;
    series = nullptr;

    chartview2 = nullptr;
    chart2 = nullptr;
    series2 = nullptr;
}

void charts::destroySeries(QPieSeries* series, QChart* chart, QChartView* chartView)
{
    if (chart->series().contains(series))
    {
        chart->removeSeries(series);
    }

    delete chart;
    delete series;
    delete chartView;
}
