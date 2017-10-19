#include "mytoolbar.h"
#include <QDebug>


MyToolBar::MyToolBar(QWidget *parent) :
    QWidget(parent)
{
    CreateWidget();
    setMinimumHeight(136); //设置纵坐标
    setMaximumHeight(136);
    setMinimumWidth(700);
}

void MyToolBar::CreateWidget()
{
    m_listStr/*<<tr("参数设置")*/<<tr("界面1")<<tr("界面2")/*<<tr("机器限时")*/;//修改客户端
    for(int nIndex=0;nIndex<2;++nIndex)
    {
        QString strImage = QString(":/image/360Buttonbg/%1.png").arg(nIndex+1);  //图片设置选项形状
        m_listBtn.append(new MyToolBtn(strImage,m_listStr[nIndex],this));
        m_listBtn.at(nIndex)->move(nIndex*87+20,0);

        connect(m_listBtn.at(nIndex),SIGNAL(signal_parent(void*)),this,SLOT(slot_set(void*)));
    }
    m_pLabel = new QLabel(this);
    m_pLabel->setPixmap(QPixmap("/*:/image/logo.png*/"));
}

void MyToolBar::resizeEvent(QResizeEvent *)
{
    m_pLabel->move(rect().width()-m_pLabel->pixmap()->width()-50,(rect().height()-m_pLabel->pixmap()->height())/2);
}

void MyToolBar::slot_set(void *pObject)
{
    for(int nIndex=0;nIndex<2;++nIndex)//修改客户端
    {
        if(m_listBtn.at(nIndex)!=pObject)
        {
            m_listBtn.at(nIndex)->SetPress(false);
        }
        else
        {
            emit signal_toolbar(nIndex+2);
            qDebug()<<"nIndex+1="<<nIndex+2;
        }
    }
}
