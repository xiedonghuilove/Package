#include "saveruntime.h"
#include "qapplication.h"
#include "qtimer.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qstringlist.h"

#ifdef Q_OS_WIN
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif

//保存运行的时间
SaveRunTime *SaveRunTime::self = 0;
SaveRunTime::SaveRunTime(QObject *parent) : QObject(parent)
{
	saveInterval = 1 * 60 * 1000;
	startTime = QDateTime::currentDateTime();
    logFile = QString("%1/%2_run_time.txt").arg(qApp->applicationDirPath()).arg(QDate::currentDate().year());

	timerSave = new QTimer(this);
	setSaveInterval(saveInterval);
	connect(timerSave, SIGNAL(timeout()), this, SLOT(saveLog()));
}

void SaveRunTime::start()
{
	timerSave->start();
	initLog();
	appendLog();
	saveLog();
}

void SaveRunTime::stop()
{
	timerSave->stop();
}

void SaveRunTime::getDiffValue(QDateTime startTime, QDateTime endTime, int &day, int &hour, int &minute)
{
	qint64 sec = startTime.secsTo(endTime);
	day = hour = minute = 0;
	int seconds = 0;

	while (sec > 0) {
		seconds++;

		if (seconds == 60) {
			minute++;
			seconds = 0;
		}

		if (minute == 60) {
			hour++;
			minute = 0;
		}

		if (hour == 24) {
			day++;
			hour = 0;
		}

		sec--;
	}
}

void SaveRunTime::initLog()
{
	//判断当前年份的记事本文件是否存在,不存在则新建并且写入标题
	//存在则自动读取最后一行的id号  记事本文件格式内容
    //编号    开始时间                结束时间                已运行时间
    //1      2016-01-01 12:33:33    2016-02-05 12:12:12     day: 0  hour: 0  minute: 0

	QFile file(logFile);

	if (file.size() == 0) {
		if (file.open(QFile::WriteOnly | QFile::Text)) {
            QString strID = QString("%1\t").arg("编号");
            QString strStartTime = QString("%1\t\t").arg("开始时间");
            QString strEndTime = QString("%1\t\t").arg("结束时间");
            QString strRunTime = QString("%1").arg("已运行时间");
#ifdef __arm__
            strStartTime = QString("%1\t\t\t").arg("开始时间");
            strEndTime = QString("%1\t\t\t").arg("结束时间");
#endif

            QString line = strID + strStartTime + strEndTime + strRunTime;

			QTextStream stream(&file);
            stream << line << NEWLINE;
			file.close();

			lastID = 0;
		}
	} else {
		if (file.open(QFile::ReadOnly)) {
			QString lastLine;

			while (!file.atEnd()) {
				lastLine = file.readLine();
			}

			file.close();

			QStringList list = lastLine.split("\t");
			lastID = list.at(0).toInt();
		}
	}

	lastID++;
}

void SaveRunTime::appendLog()
{
	QFile file(logFile);

	//写入当前首次运行时间
	if (file.open(QFile::WriteOnly | QFile::Append | QFile::Text)) {
		QString strID = QString("%1\t").arg(lastID);
		QString strStartTime = QString("%1\t").arg(startTime.toString("yyyy-MM-dd HH:mm:ss"));
        QString strEndTime = QString("%1\t").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

		int day, hour, minute;
		getDiffValue(startTime, QDateTime::currentDateTime(), day, hour, minute);
		QString strRunTime = QString("%1 天 %2 时 %3 分").arg(day).arg(hour).arg(minute);
		QString line = strID + strStartTime + strEndTime + strRunTime;

		QTextStream stream(&file);
        stream << line << NEWLINE;
		file.close();
	}
}

void SaveRunTime::saveLog()
{
	//每次保存都是将之前的所有文本读取出来,然后替换最后一行即可
	QFile file(logFile);

	//如果日志文件不存在,则初始化一个日志文件
	if (file.size() == 0) {
		initLog();
		appendLog();
		return;
	}

	if (file.open(QFile::ReadWrite)) {
		//一行行读取到链表
		QStringList content;

		while (!file.atEnd()) {
			content.append(file.readLine());
		}

		//重新清空文件
		file.resize(0);
		QString lastLine = content.last();
		QStringList list = lastLine.split("\t");

		//计算已运行时间
		int day, hour, minute;
		getDiffValue(startTime, QDateTime::currentDateTime(), day, hour, minute);
		QString strRunTime = QString("%1 天 %2 时 %3 分").arg(day).arg(hour).arg(minute);

		//重新拼接最后一行
        list[2] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
		list[3] = strRunTime;
		lastLine = list.join("\t");

		//重新替换最后一行并写入新的数据
		content[content.count() - 1] = lastLine;

		QTextStream stream(&file);
        stream << content.join("") << NEWLINE;
        file.close();
	}
}

void SaveRunTime::setSaveInterval(int saveInterval)
{
	this->saveInterval = saveInterval;
	timerSave->setInterval(saveInterval);
}
