#include "mycontentwidget.h"

// ???? 怎么实现点击那个Button后进入另一个窗口
MyContentWidget::MyContentWidget(QWidget *parent) :
    QWidget(parent)
{
    CreateWidget();
    CreatLayout();
    SetWindowStyle();
}

void MyContentWidget::CreateWidget()
{
    m_widget = new Widget(this);
    m_widget1 = new Widget1(this);

    m_vboxLayout = new QVBoxLayout(this);//垂直布局
    m_vboxLayout->addWidget(m_widget);
    m_vboxLayout->addWidget(m_widget1);

    m_widget1->close();

}

void MyContentWidget::CreatLayout()
{

}

void MyContentWidget::SetWindowStyle()
{

}


void MyContentWidget::slot_toolbar(int nIndex)
{
    switch(nIndex)
    {
        case 1:break;//界面1
        case 2:m_widget->show();m_widget1->close(); break;//界面2
        case 3:m_widget->close();m_widget1->show();break;//界面3
        case 4:break;
        default:
            break;
    }
}


