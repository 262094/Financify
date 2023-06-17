#include "charts.h"


charts::charts(QMainWindow *parent)
    : QMainWindow(parent)
    , m_dbManager(DatabaseManager::getInstance())
{

    ChartCreated = false;
}

void charts::createChart(QFrame *frame1, QFrame *frame2)
{


    if (ChartCreated)
        return;

    QPieSeries *series = new QPieSeries();
    QPieSeries *series2 = new QPieSeries();
    m_dbManager.chartView(series, series2);

    QChart *chart = new QChart();
    chart -> addSeries(series);
    chart -> setTitle("Chart of your income");
    QFont titleFont;
    titleFont.setPointSize(20); // Ustawienie rozmiaru na 20
    chart->setTitleFont(titleFont);
    QChartView *chartview = new QChartView(chart);
    chartview -> setParent (frame1);
    series->setLabelsVisible(true);
    // Ustawienie wyświetlania etykiet procentowych dla każdej części wykresu
    for (QPieSlice *slice : series->slices()) {
        QString label = QString("%1%").arg(100.0 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(QString("%1\n(%2)").arg(slice->label()).arg(label));
    }
    QChartView *chartView = new QChartView(chart);
    chartView->setParent(frame1);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setMinimumSize(600, 320); // Minimalny rozmiar wykresu
    frame1->layout()->addWidget(chartView); // Dodanie wykresu do układu
    // Dodatkowo, jeśli korzystasz z okna głównego, możesz ustawić odpowiednią właściwość
    // dla przystosowania wykresu do rozmiaru okna głównego
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QChart *chart2 = new QChart();
    chart2 -> addSeries(series2);
    chart2 -> setTitle("Chart of your expenses");
    QFont titleFont2;
    titleFont2.setPointSize(20); // Ustawienie rozmiaru na 20
    chart2->setTitleFont(titleFont2);
    QChartView *chartview2 = new QChartView(chart2);
    chartview2 -> setParent (frame2);
    series2->setLabelsVisible(true);
    // Ustawienie wyświetlania etykiet procentowych dla każdej części wykresu
    for (QPieSlice *slice : series2->slices()) {
        QString label = QString("%1%").arg(100.0 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(QString("%1\n(%2)").arg(slice->label()).arg(label));
    }
    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setParent(frame2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView2->setMinimumSize(600, 310); // Minimalny rozmiar wykresu
    frame2->layout()->addWidget(chartView2); // Dodanie wykresu do układu
    // Dodatkowo, jeśli korzystasz z okna głównego, możesz ustawić odpowiednią właściwość
    // dla przystosowania wykresu do rozmiaru okna głównego
    chartView2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ChartCreated = true;
}




