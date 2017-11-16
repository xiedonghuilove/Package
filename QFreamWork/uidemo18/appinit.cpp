#include "appinit.h"
#include "qmutex.h"
#include "qapplication.h"
#include "qevent.h"
#include "qwidget.h"

AppInit *AppInit::self = 0;
AppInit *AppInit::Instance()
{
    if (!self) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!self) {
            self = new AppInit;
        }
    }

    return self;
}

//构造函数
AppInit::AppInit(QObject *parent) : QObject(parent)
{
}

//重写事件过滤器
bool AppInit::eventFilter(QObject *obj, QEvent *evt)//参数：对象，事件
{
    QWidget *w = (QWidget *)obj;//强制转换为QWidget
    if (!w->property("canMove").toBool())//得到QWidget的属性是canMove(可以移动)。
    {
        return QObject::eventFilter(obj, evt);
    }

    static QPoint mousePoint;//静态变量 --> 鼠标坐标
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress)//事件类型  鼠标按钮按下
    {
        if (event->button() == Qt::LeftButton) //左键
        {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease) //事件类型  鼠标按钮释放
    {
        mousePressed = false;
        return true;
    }
    else if (event->type() == QEvent::MouseMove)//事件类型  鼠标移动
    {
        if (mousePressed && (event->buttons() && Qt::LeftButton))
        {
            w->move(event->globalPos() - mousePoint);//窗体移动坐标
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}

//加载事件过滤器
void AppInit::start()
{
    qApp->installEventFilter(this);
}
