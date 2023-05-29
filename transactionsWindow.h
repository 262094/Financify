#ifndef TRANSACTIONSWINDOW_H
#define TRANSACTIONSWINDOW_H

#include <QDialog>
#include <QMouseEvent>

#include "transactions.h"

class Transactions;

namespace Ui {
class transactionsWindow;
}

class transactionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit transactionsWindow(Transactions* transactions, QWidget *parent = nullptr);
    ~transactionsWindow();

    void show();

private slots:
    void on_submitButton_clicked();

private:
    Ui::transactionsWindow *ui;

    Transactions* m_transactions;

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // TRANSACTIONSWINDOW_H
