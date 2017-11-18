#include "applog.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qapplication.h"
#include "qstringlist.h"
#include "qdatetime.h"

#define QDATE qPrintable (QDate::currentDate().toString("yyyy-MM-dd"))
#define AppName "API"
#define AppPath qApp->applicationDirPath()

QFile *logFile = new QFile;
QString logFileName;

//输出所有打印调试信息到日志文件
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
void Log(QtMsgType type, const char *msg)
#else
void Log(QtMsgType type, const QMessageLogContext &, const QString &msg)
#endif
{
	QString content;

	switch (type) {
		case QtDebugMsg:
			content = QString("%1").arg(msg);
			break;

		case QtWarningMsg:
			content = QString("%1").arg(msg);
			break;

		case QtCriticalMsg:
			content = QString("%1").arg(msg);
			break;

		case QtFatalMsg:
			content = QString("%1").arg(msg);
			break;
	}

	if (content.startsWith("libpng")) {
		return;
	}

	//方法改进:之前每次输出日志都打开文件,改成只有当日期改变时才新建和打开文件
	QString fileName = QString("%1/%2_Log_%3.txt").arg(AppPath).arg(AppName).arg(QDATE);

	if (fileName != logFileName) {
		logFileName = fileName;

		if (logFile->isOpen()) {
			logFile->close();
		}

		logFile->setFileName(logFileName);
		logFile->open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
	}

	QTextStream logStream(logFile);
	logStream << content << "\n";
}

AppLog *AppLog::self = 0;
AppLog::AppLog(QObject *parent) : QObject(parent)
{
}

//安装日志钩子,输出调试信息到文件,便于调试
void AppLog::start()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
	qInstallMsgHandler(Log);
#else
	qInstallMessageHandler(Log);
#endif
}

//卸载日志钩子
void AppLog::stop()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
	qInstallMsgHandler(0);
#else
	qInstallMessageHandler(0);
#endif
}
