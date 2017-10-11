#include "widget.h"
#include <QApplication>
#include <QCoreApplication>
#include "main_window.h"
#include "titlebar.h"
#include "simple_edit.h"
#include "simple_mode.h"
#include "scientific_mode.h"
#include "mybasedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
