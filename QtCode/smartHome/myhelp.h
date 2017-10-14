#ifndef MYHELP
#define MYHELP
#include <QFile>
#include <QtCore>
#include <QtGui>
#include <QDesktopWidget>

class myHelper:public QObject
{
public:

    //设置皮肤样式
    static void setStyle(const QString &styleName)
    {
        QFile file(QString("%1").arg(styleName));
        file.open(QFile::ReadOnly);
        QString css = QLatin1String(file.readAll());
        qApp->setStyleSheet(css);
        qDebug()<<"ok!";
    }

};

#endif // MYHELP

