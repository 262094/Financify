#ifndef GOALSWINDOW_H
#define GOALSWINDOW_H

#include <QDialog>
#include <QMouseEvent>

#include "goals.h"

class Goals;

namespace Ui {
class goalsWindow;
}

class goalsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit goalsWindow(Goals * goals, QWidget *parent = nullptr);
    ~goalsWindow();

    void show();

private slots:
    void on_submitButton_clicked();

    void on_closeButton_5_clicked();

private:
    Ui::goalsWindow *ui;

    Goals * m_goals;

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // GOALSWINDOW_H
