#ifndef SIMPLEMODE_H
#define SIMPLEMODE_H

#include <QWidget>
#include "simple_button.h"
#include "simple_edit.h"
#include <QGridLayout>
#include <QKeyEvent>
#include "core/evaluator.h"

class SimpleMode : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleMode(QWidget *parent = 0);
    SimpleEdit *editText;
private://私有变量
    QGridLayout *layout;//栅格布局

    SimpleButton *clearButton;//清除按钮
    SimpleButton *backButton;//返回按钮
    SimpleButton *divButton;//除法
    SimpleButton *multButton;//乘法
    SimpleButton *sevenButton;//7
    SimpleButton *eightButton;//8
    SimpleButton *nineButton;//9
    SimpleButton *minusButton;//减法
    SimpleButton *fourButton;//4
    SimpleButton *fiveButton;//5
    SimpleButton *sixButton;//6
    SimpleButton *plusButton;//加
    SimpleButton *oneButton;//1
    SimpleButton *twoButton;//2
    SimpleButton *threeButton;//3
    SimpleButton *zeroButton;//0
    SimpleButton *pointButton;//.
    SimpleButton *equalButton;//等于

    Evaluator* m_evaluator;//计算器类

    void initUI();
protected:
    void keyPressEvent(QKeyEvent *);//重新按键事件


signals:

public slots:
public slots:
    void on_clear_button_clicked();
    void on_back_button_clicked();
    void on_div_button_clicked();
    void on_mult_button_clicked();
    void on_seven_button_clicked();
    void on_eight_button_clicked();
    void on_nine_button_clicked();
    void on_minus_button_clicked();
    void on_four_button_clicked();
    void on_five_button_clicked();
    void on_six_button_clicked();
    void on_plus_button_clicked();
    void on_one_button_clicked();
    void on_two_button_clicked();
    void on_three_button_clicked();
    void on_zero_button_clicked();
    void on_point_button_clicked();
    void on_equal_button_clicked();

    void on_number_button_clicked(const QString &text);
    void on_symbol_button_clicked(const QString &text);
};

#endif // SIMPLEMODE_H
