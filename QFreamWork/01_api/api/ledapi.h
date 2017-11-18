#ifndef LEDAPI_H
#define LEDAPI_H

#include <QObject>
#include <QMutex>

class QPixmap;

class LEDAPI : public QObject
{
	Q_OBJECT
public:
	explicit LEDAPI(QObject *parent = 0);
	static LEDAPI *Instance()
	{
		static QMutex mutex;

		if (!self) {
			QMutexLocker locker(&mutex);

			if (!self) {
				self = new LEDAPI;
			}
		}

		return self;
	}

	QPixmap getLEDPix(QString text, int width, int height, QString fontName, int fontSize, int step);
	QByteArray getLEDPixData(QString text, int width, int height, QString fontName, int fontSize, int step);

private:
	static LEDAPI *self;

signals:

public slots:
};

#endif // LEDAPI_H
