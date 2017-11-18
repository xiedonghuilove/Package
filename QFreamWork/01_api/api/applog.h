#ifndef APPLOG_H
#define APPLOG_H

#include <QObject>
#include <QMutex>

class AppLog : public QObject
{
	Q_OBJECT
public:
	explicit AppLog(QObject *parent = 0);
	static AppLog *Instance()
	{
		static QMutex mutex;

		if (!self) {
			QMutexLocker locker(&mutex);

			if (!self) {
				self = new AppLog;
			}
		}

		return self;
	}

	void start();
	void stop();

private:
	static AppLog *self;
};

#endif // APPLOG_H
