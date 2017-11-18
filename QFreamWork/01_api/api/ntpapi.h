#ifndef NTPAPI_H
#define NTPAPI_H

#include <QObject>
#include <QMutex>
#include <QDateTime>

class QUdpSocket;

class NTPAPI : public QObject
{
	Q_OBJECT
public:
	explicit NTPAPI(QObject *parent = 0);
	static NTPAPI *Instance()
	{
		static QMutex mutex;

        if (!self) {
			QMutexLocker locker(&mutex);

            if (!self) {
                self = new NTPAPI;
			}
		}

        return self;
	}

private:
    static NTPAPI *self;
	QUdpSocket *udpSocket;

private slots:
	void readData();
	void sendData();

signals:
	void receiveTime(QDateTime dateTime);

public slots:
	void getTime(QString ntpIP);

};

#endif // NTPAPI_H
