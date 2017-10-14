#ifndef MODELCHOOSEWIDGET_H
#define MODELCHOOSEWIDGET_H

#include <QWidget>

namespace Ui {
class ModelChooseWidget;
}

class ModelChooseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelChooseWidget(QWidget *parent = 0);
    ~ModelChooseWidget();

private slots:
    void on_pbn_leve_home_clicked();

    void on_pbn_go_home_clicked();

    void on_pbn_key_led_clicked();

private:
    Ui::ModelChooseWidget *ui;
        bool FlagSTateHome;
        bool FlagSTateHome1;
        bool FlagSTateHome2;
        int a;
};

#endif // MODELCHOOSEWIDGET_H
