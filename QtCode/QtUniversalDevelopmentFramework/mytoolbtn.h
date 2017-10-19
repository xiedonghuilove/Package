#ifndef MYTOOLBTN_H
#define MYTOOLBTN_H

#include <QToolButton>
#include <QPainter>
class MyToolBtn : public QToolButton
{
    Q_OBJECT
public:
    explicit MyToolBtn(QWidget *parent = 0);
    MyToolBtn(const QString &strImage,const QString &strInfo,QWidget *parent=0);
    
    bool m_bOver,m_bPress;
    QString m_strImage,m_strInfo;

    void SetPress(bool bEnable);
    void SetOver(bool bEnable);
    void painterInfo(QPainter *pPainter);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);

signals:
    void signal_parent(void*);
public slots:
    void slot_press(void);
    
};

#endif // MYTOOLBTN_H
