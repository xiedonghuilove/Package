#ifndef SAVERUNTIME_H
#define SAVERUNTIME_H

#include <QObject>
#include <QMutex>
#include <QDateTime>

class QTimer;

class SaveRunTime : public QObject
{
    Q_OBJECT
public:
    explicit SaveRunTime(QObject *parent = 0);
    static SaveRunTime *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new SaveRunTime;
            }
        }

        return self;
    }

    void start();
    void stop();    

private:
    static SaveRunTime *self;
    int lastID;
    int saveInterval;
    QDateTime startTime;
    QString logFile;
    QTimer *timerSave;

private:
    void getDiffValue(QDateTime startTime, QDateTime endTime, int &day, int &hour, int &minute);

signals:

public slots:    
    void initLog();     //初始化日志文件
    void appendLog();   //追加一条记录到日志文件
    void saveLog();     //保存运行时间到日志文件
    void setSaveInterval(int saveInterval);
};

#endif // SAVERUNTIME_H
