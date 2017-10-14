#ifndef CURTAINWIDGET_H
#define CURTAINWIDGET_H

#include <QWidget>

namespace Ui {
class CurtainWidget;
}

class CurtainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurtainWidget(QWidget *parent = 0);
    ~CurtainWidget();

private slots:
    void on_pbnOpenCurtain_clicked();

    void on_pbnStopCurtain_clicked();

    void on_pbnCloseCurtain_clicked();

private:
    Ui::CurtainWidget *ui;
};

#endif // CURTAINWIDGET_H
