#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include "bedroomwidget.h"
#include "curtainwidget.h"
#include "musicwidget.h"
#include "modelchoosewidget.h"
#include "parlourwidget.h"
#include "kitchenwidget.h"
#include "systemsettingdialog.h"
#include "statisticwidget.h"
//统计界面
class BedRoomWidget;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    enum enum_widget{
        E_Control_WIDGET = 0,       //控制主页
        E_HOME_WIDGET,              //首页
        E_BEDROOM_WIDGET=2,           //卧室
        E_CURTAIN_WIDGET=3,           //窗帘界面
        E_MUSIC_WIDGET=4,              //音乐播放界面
        E_MODEL_WIDGET=5,             //模式控制
        E_PARLOUR_WIDGET = 6,       //客厅
        E_KITCHEN_WIDGET = 7,           //厨房
        E_TEMPTURE = 8,             //统计
        E_NIGHT_WIDGET,             //夜间模式
        E_SECURITY_WIDGET,          //安防管理界面



    };

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    void initForm();
    void initWidget();
    void startAnimation();
    void initDataTime();


    void setCurrentWidget(enum_widget enum_widget_name);


private slots:

    void slotShowCurrentDataTime();
    void on_tbnControl_clicked();


    void on_tbnHome_clicked();

    void on_tbnBedRoom_clicked();

    void on_tbnCurtain_clicked();

    void on_tbnMusic_clicked();

    void on_tbnModel_clicked();

    void on_tbnParlor_clicked();

    void on_tbnKitchen_clicked();

    void on_tbnSetting_clicked();

    void on_tbnStasistion_clicked();

    void on_tbnSafety_clicked();

private:
    Ui::Widget *ui;
    QTimer *m_timer;

    SystemSettingDialog *m_settingDialog;           //设置界面
    Parlourwidget *m_parlourWidget;                 //客厅界面
    BedRoomWidget *m_bedRoomWidget;                 //卧室界面
    KitchenWidget *m_kitchenWidget;                 //厨房界面
    StatisticWidget *m_statisticWidget;             //统计界面
//    EntertainmentWidget *m_entertainmentWidget;     //娱乐界面
//    NightWidget *m_nightWidget;                     //夜间界面
//    SecurityWidget *m_securityWidget;               //安防监控界面
    CurtainWidget *m_curtainWidget;                 //窗帘界面
    ModelChooseWidget *m_modelWidget;               //模式选择控制界面
    MusicWidget *m_musicPlayWidget;                 //音乐播放界面
};

#endif // WIDGET_H
