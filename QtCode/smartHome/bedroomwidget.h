#ifndef BEDROOMWIDGET_H
#define BEDROOMWIDGET_H

#include <QWidget>

namespace Ui {
class BedRoomWidget;
}

class BedRoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BedRoomWidget(QWidget *parent = 0);
    ~BedRoomWidget();

private slots:
    void on_pbn_light_left_clicked();

    void on_pbn_light_right_clicked();

private:
    Ui::BedRoomWidget *ui;
    QString m_styleOn;                  //灯打开
    QString m_styleOff;                 //灯关闭

    int a;
    bool Flag,Flag1;
};

#endif // BEDROOMWIDGET_H
