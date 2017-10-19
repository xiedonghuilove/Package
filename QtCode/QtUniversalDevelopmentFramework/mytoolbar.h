#ifndef MYTOOLBAR_H
#define MYTOOLBAR_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QPixmap>
#include "mytoolbtn.h"

class MyToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit MyToolBar(QWidget *parent = 0);
    
    QList<MyToolBtn*> m_listBtn;
    QList<QString> m_listStr;
    QLabel * m_pLabel;

    void CreateWidget(void);


    void resizeEvent(QResizeEvent *);
signals:
    void signal_toolbar(int);
public slots:
    void slot_set(void *pObject);
    
};

#endif // MYTOOLBAR_H
