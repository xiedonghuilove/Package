#ifndef MYCONTENTWIDGET_H
#define MYCONTENTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "widget.h"
#include "widget1.h"



class MyContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyContentWidget(QWidget *parent = 0);

    Widget *m_widget;
    Widget1 *m_widget1;

     QVBoxLayout *m_vboxLayout;//垂直布局

    void CreateWidget();
    void CreatLayout();
    void SetWindowStyle();
signals:
    
public slots:
    void slot_toolbar(int);

};

#endif // MYCONTENTWIDGET_H
