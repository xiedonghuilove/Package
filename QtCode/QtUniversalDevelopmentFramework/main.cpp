#include "widget.h"
#include <QApplication>
#include "mymainwindow.h"
#include "mytitlebar.h"
#include "mytoolbar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow w;
    w.show();

    return a.exec();
}
