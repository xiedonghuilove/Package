#include "widget.h"
#include <QApplication>
#include "myhelp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myHelper::setStyle(":/images/css/style.css");         //加载样式表

    Widget w;
    w.show();

    return a.exec();
}
