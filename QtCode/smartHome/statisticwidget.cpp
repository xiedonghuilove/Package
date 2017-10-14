#include "statisticwidget.h"
#include "ui_statisticwidget.h"
#include "control.h"
#include <QDateTime>
#include <QDate>

//纵坐标最大值
#define PLOT_TEMPTURE_MAX_Y         100     //温度值
#define PLOT_HUMIDITY_MAX_Y         100     //湿度值
#define PLOT_SMOKE_MAX_Y            100   //烟雾浓度值

#define TextColor QColor(255,255,0)         //黄色
#define Plot_NoColor QColor(0,0,0,0)        //黑色

#define Plot1_DotColor QColor(5,189,251)
#define Plot1_LineColor QColor(41,138,220)
#define Plot1_BGColor QColor(41,138,220,80)

#define Plot2_DotColor QColor(236,110,0)
#define Plot2_LineColor QColor(246,98,0)
#define Plot2_BGColor QColor(246,98,0,80)

#define Plot3_DotColor QColor(204,0,0)
#define Plot3_LineColor QColor(246,0,0,200)
#define Plot3_BGColor QColor(246,98,0,80)

#define Plot1_Count 20
#define Plot2_Count 10

#define Plot1_MaxY 50
#define Plot2_MaxY 100
#define Plot3_MaxY 500
#define Plot4_MaxY 100

#define TextWidth 2
#define LineWidth 3
#define DotWidth  10

#ifdef _ARM_
#define Plot5_MaxY 20
#else
#define Plot5_MaxY 50
#endif


StatisticWidget::StatisticWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticWidget)
{
    ui->setupUi(this);

    initForm();

    initPlot();

    initPlotTempture();
    initPlotHumidity();
    initPlotSmoke();

}

StatisticWidget::~StatisticWidget()
{
    delete ui;
}


void StatisticWidget::initForm()
{
    m_currentIndex = 0;

    m_plots_list.append(ui->plot_tempture);
    m_plots_list.append(ui->plot_humidity);
    m_plots_list.append(ui->plot_smoke);

}

//初始化绘图设备
void StatisticWidget::initPlot()
{
    //设置各个图的纵坐标名称
    m_plots_list.at(0)->yAxis->setLabel(tr("温度值(单位:°)"));
    m_plots_list.at(1)->yAxis->setLabel(tr("湿度值(单位:%)"));
    m_plots_list.at(2)->yAxis->setLabel(tr("浓度值(单位:%)"));

    //设置纵坐标范围
    m_plots_list.at(0)->yAxis->setRange(0,PLOT_TEMPTURE_MAX_Y);
    m_plots_list.at(1)->yAxis->setRange(0,PLOT_HUMIDITY_MAX_Y);
    m_plots_list.at(2)->yAxis->setRange(0,PLOT_SMOKE_MAX_Y);

    foreach (QCustomPlot *plot, m_plots_list) {
        //设置坐标颜色，名称
        plot->yAxis->setLabelColor(TextColor);

        plot->yAxis->setTickLabelColor(TextColor);  //Y轴标签颜色
        plot->xAxis->setTickLabelColor(TextColor);

        plot->xAxis->setBasePen(QPen(TextColor,TextWidth));
        plot->yAxis->setBasePen(QPen(TextColor,TextWidth));

        plot->xAxis->setTickPen(QPen(TextColor,TextWidth));
        plot->yAxis->setTickPen(QPen(TextColor,TextWidth));

        plot->xAxis->setSubTickPen(QPen(TextColor,TextWidth));
        plot->yAxis->setSubTickPen(QPen(TextColor,TextWidth));

        //设置画布背景
        QLinearGradient plotGradient;
        plotGradient.setStart(0,0);
        plotGradient.setFinalStop(0,350);
        plotGradient.setColorAt(0,QColor(80,80,80));
        plotGradient.setColorAt(1,QColor(50,50,50));
        plot->setBackground(plotGradient);

        //设置坐标背景色
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0,0);
        axisRectGradient.setFinalStop(0,350);
        axisRectGradient.setColorAt(0,QColor(80,80,80));
        axisRectGradient.setColorAt(1,QColor(30,30,30));
        plot->axisRect()->setBackground(axisRectGradient);

        //设置图例提示位置以及背景色
        plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);
        plot->legend->setBrush(QColor(255, 255, 255, 200));

        plot->replot();
    }
}

//初始化温度统计图
void StatisticWidget::initPlotTempture()
{
    m_plot_tempture_labels <<tr("星期一")<<tr("星期二")<<tr("星期三")
                          <<tr("星期四")<<tr("星期五")
                         <<tr("星期六")<<tr("星期日");
    //向画布添加一条曲线
    m_plots_list.at(0)->addGraph();
    m_plots_list.at(0)->graph(0)->setName(tr("温度值(单位:度)"));
    m_plots_list.at(0)->graph(0)->setPen(QPen(Plot1_LineColor,LineWidth));
    m_plots_list.at(0)->graph(0)->setScatterStyle(
                QCPScatterStyle(QCPScatterStyle::ssCircle,
                                QPen(Plot1_DotColor, LineWidth),
                                QBrush(Plot1_DotColor), DotWidth));
    //设置静态曲线的横坐标范围以及自适应坐标
    m_plots_list.at(0)->xAxis->setAutoTicks(false);
    m_plots_list.at(0)->xAxis->setAutoTickLabels(false);
    m_plots_list.at(0)->xAxis->setRange(0,8);

    //设置纵坐标数据间隔(温度间隔)
    m_plots_list.at(0)->yAxis->setAutoTickStep(false);
    m_plots_list.at(0)->yAxis->setTickStep(10);

    //设置横坐标标签以及个数(这两个必须匹配)
    m_plot_tempture_keys <<1<<2<<3<<4<<5<<6<<7;
    m_plots_list.at(0)->xAxis->setTickVector(m_plot_tempture_keys);
    m_plots_list.at(0)->xAxis->setTickVectorLabels(m_plot_tempture_labels);
}

//初始化湿度统计图
void StatisticWidget::initPlotHumidity()
{
    //向画布添加一条曲线
    m_plots_list.at(1)->addGraph(0);
    m_plots_list.at(1)->graph(0)->setName(tr("湿度值(单位:%)"));
    m_plots_list.at(1)->graph(0)->setPen(QPen(Plot2_LineColor,LineWidth));
    m_plots_list.at(1)->graph(0)->setScatterStyle(
                QCPScatterStyle(QCPScatterStyle::ssCircle,
                                QPen(Plot2_DotColor, LineWidth),
                                QBrush(Plot2_DotColor), DotWidth));

    //设置动态曲线的横坐标格式及范围
    m_plots_list.at(1)->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    m_plots_list.at(1)->xAxis->setDateTimeFormat("HH:mm:ss");
    m_plots_list.at(1)->xAxis->setAutoTickStep(false);
    m_plots_list.at(1)->xAxis->setTickStep(1);
    m_plots_list.at(1)->xAxis->setRange(0, Plot2_Count, Qt::AlignRight);
}

//初始化烟雾统计图
void StatisticWidget::initPlotSmoke()
{
    m_plots_list.at(2)->addGraph(0);
    m_plots_list.at(2)->graph(0)->setName(tr("烟雾值(单位:%)"));
    m_plots_list.at(2)->graph(0)->setPen(QPen(Plot3_LineColor,LineWidth));
    m_plots_list.at(2)->graph(0)->setScatterStyle(
                QCPScatterStyle(QCPScatterStyle::ssCircle,
                                QPen(Plot3_DotColor, LineWidth),
                                QBrush(Plot3_DotColor), DotWidth));

    m_plots_list.at(2)->xAxis->setRange(0,10,Qt::AlignLeft);
    m_plots_list.at(2)->yAxis->setRange(0,50,Qt::AlignBottom);
    m_plots_list.at(2)->xAxis->setTickStep(1);
    m_plots_list.at(2)->yAxis->setTickStep(1);
    m_plots_list.at(2)->yAxis->setAutoTickStep(false);
    m_plots_list.at(2)->yAxis->setAutoTickCount(1);
    m_plots_list.at(2)->graph(0)->rescaleAxes();
    m_plots_list.at(2)->replot();
}

//开启/关闭移动缩放功能
void StatisticWidget::on_ckMove_stateChanged(int arg1)
{
    bool value = (arg1 == 0? false:true);
    if (value)
    {
        ui->plot_tempture->setInteractions(QCP::iRangeDrag |QCP::iRangeZoom);
        ui->plot_humidity->setInteractions(QCP::iRangeDrag |QCP::iRangeZoom);
        ui->plot_smoke->setInteractions(QCP::iRangeDrag |QCP::iRangeZoom);
    }else
    {
        ui->plot_tempture->setInteractions(QCP::iSelectOther);
        ui->plot_humidity->setInteractions(QCP::iSelectOther);
        ui->plot_smoke->setInteractions(QCP::iSelectOther);
    }
}

//打开/关闭背景
void StatisticWidget::on_ckBackground_stateChanged(int arg1)
{
    bool value = (arg1 == 0? false:true);
    if (value)
    {
        m_plots_list.at(0)->graph(0)->setBrush(QBrush(Plot1_BGColor));
        m_plots_list.at(1)->graph(0)->setBrush(QBrush(Plot2_BGColor));
        m_plots_list.at(2)->graph(0)->setBrush(QBrush(Plot3_BGColor));
    }else
    {
        m_plots_list.at(0)->graph(0)->setBrush(QBrush(Plot_NoColor));
        m_plots_list.at(1)->graph(0)->setBrush(QBrush(Plot_NoColor));
        m_plots_list.at(2)->graph(0)->setBrush(QBrush(Plot_NoColor));
    }

    m_plots_list.at(0)->replot();
    m_plots_list.at(1)->replot();
    m_plots_list.at(2)->replot();
}

//添加/取消图例
void StatisticWidget::on_ckText_stateChanged(int arg1)
{
    bool value = (arg1 == 0? false:true);
    if (value)
    {
        m_plots_list.at(0)->legend->setVisible(true);
        m_plots_list.at(1)->legend->setVisible(true);
        m_plots_list.at(2)->legend->setVisible(true);
    }else
    {
        m_plots_list.at(0)->legend->setVisible(false);
        m_plots_list.at(1)->legend->setVisible(false);
        m_plots_list.at(2)->legend->setVisible(false);
    }

    //重绘
    m_plots_list.at(0)->replot();
    m_plots_list.at(1)->replot();
    m_plots_list.at(2)->replot();
}

