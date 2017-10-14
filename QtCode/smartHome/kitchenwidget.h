#ifndef KITCHENWIDGET_H
#define KITCHENWIDGET_H

#include <QWidget>
#include <QToolButton>

namespace Ui {
class KitchenWidget;
}

class KitchenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KitchenWidget(QWidget *parent = 0);
    ~KitchenWidget();

private slots:
    void on_pbn_light_main_clicked();

    void on_tbn_smoke_sub_clicked();

    void on_tbn_smoke_add_clicked();

private:
    Ui::KitchenWidget *ui;
    QString m_styleOn;
    QString m_styleoff;
    int smorkcur;
    int a;
    bool Flag;

    void setToolButtonStyle(QToolButton *tbn,
                               const QString &text,
                              const QString iconName);

};

#endif // KITCHENWIDGET_H
