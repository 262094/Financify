#ifndef CHARTSWINDOW_H
#define CHARTSWINDOW_H

#include <QDialog>

namespace Ui {
class chartswindow;
}

class chartswindow : public QDialog
{
    Q_OBJECT

public:
    explicit chartswindow(QWidget *parent = nullptr);
    ~chartswindow();

private:
    Ui::chartswindow *ui;
};

#endif // CHARTSWINDOW_H
