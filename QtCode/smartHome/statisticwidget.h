#ifndef STATISTICWIDGET_H
#define STATISTICWIDGET_H

#include <QWidget>
#include "qcustomplot.h"


namespace Ui {
class StatisticWidget;
}

class StatisticWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticWidget(QWidget *parent = 0);
    ~StatisticWidget();

private slots:
//    void loadPlotTempture();                //加载温度绘图
//    void loadPlotHumidity();                //加载湿度绘图
//    void loadPlotSmoke();                   //加载烟雾浓度绘图

    void on_ckMove_stateChanged(int arg1);

    void on_ckBackground_stateChanged(int arg1);

    void on_ckText_stateChanged(int arg1);

//    void slotUpdataData();                  //更新统计图数据

private:
    Ui::StatisticWidget *ui;

    int m_currentIndex;                       //当前界面id
    QList<QCustomPlot *> m_plots_list;

    QVector<double> m_plot_tempture_keys;
    QVector<QString> m_plot_tempture_labels;
    QVector<double> m_plot_tempture_values;

    double plot2_key;
    double plot2_value;

    QVector<double> m_plot_smoke_values;
    QVector<double> m_plot_smoke_key;
    int m_smoke_count;

    void initStyle();                       //初始化样式
    void initForm();                        //初始化界面
    void initPlot();                        //初始化绘图
    void initPlotTempture();                //初始化温度绘图
    void initPlotHumidity();                //初始化湿度绘图
    void initPlotSmoke();                   //初始化烟雾浓度绘图

};

#endif // STATISTICWIDGET_H
