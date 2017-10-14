#ifndef PARLOURWIDGET_H
#define PARLOURWIDGET_H

#include <QWidget>
#include <QToolButton>

namespace Ui {
class Parlourwidget;
}

class Parlourwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Parlourwidget(QWidget *parent = 0);
    ~Parlourwidget();
private slots:
    void on_pbn_light_main_clicked();

    void on_pbn_light_top_clicked();

    void on_pbn_light_help_clicked();

    void on_tbn_temp_add_clicked();

    void on_tbn_temp_sub_clicked();

    void on_tbn_hum_add_clicked();

    void on_tbn_hum_sub_clicked();

private:
    //设置按钮的样式函数。
    void setToolButtonStyle(QToolButton*tbn, const QString &text,
                            const QString iconName);

private:
    Ui::Parlourwidget *ui;
    QString m_styleOn;
    QString m_styleoff;
    bool flagLightmain;
    bool flagLighttop;
    bool flagLighthelp;
    int a;
    int tempcur,shiducur;
};

#endif // PARLOURWIDGET_H
