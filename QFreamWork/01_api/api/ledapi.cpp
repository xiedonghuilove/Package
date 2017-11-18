#include "ledapi.h"
#include "qpixmap.h"
#include "qpainter.h"

LEDAPI *LEDAPI::self = 0;
LEDAPI::LEDAPI(QObject *parent) : QObject(parent)
{

}

QPixmap LEDAPI::getLEDPix(QString text, int width, int height, QString fontName, int fontSize, int step)
{
	QPixmap pix(width, height);
	pix.fill((QColor(0, 0, 0)));
	QPainter paint(&pix);

	QImage image(160, 16, QImage::Format_MonoLSB);
	QPainter painter(&image);
	QRgb backColor = qRgb(255, 255, 255);
	image.fill(backColor);

	QFont font;
	font.setFamily(fontName);
	font.setPointSize(fontSize);

	QFont font2;
	font2.setFamily(fontName);
	font2.setPointSize(fontSize / 2);
	paint.setFont(font2);

	painter.setFont(font);
	painter.drawText(image.rect(), Qt::AlignLeft | Qt::AlignVCenter, text);

	int i, j, k, x, y;
	y = step;

	for (i = 0; i < 16; i++) {
		uchar *lineByte = image.scanLine(i);
		x = 0;

		for (j = 0; j < 20; j++) {
			uchar tp = lineByte[j];
			QString strBin;

			for (k = 0; k < 8; k++) {
				if (tp & 0x01) {
					paint.setPen(QColor(22, 22, 22));
					strBin += "0";
				} else {
					paint.setPen(QColor(255, 0, 0));
					strBin += "1";
				}

				paint.drawText(x, y, "●");
				x += step;
				tp >>= 1;
			}
		}

		y += step;
	}

	return pix;
}

QByteArray LEDAPI::getLEDPixData(QString text, int width, int height, QString fontName, int fontSize, int step)
{
	QImage image(width, height, QImage::Format_MonoLSB);
	QPainter painter(&image);
	QRgb backColor = qRgb(255, 255, 255);
	image.fill(backColor);

	QFont font;
	font.setFamily(fontName);
	font.setPointSize(fontSize);

	painter.setFont(font);
	painter.drawText(image.rect(), Qt::AlignLeft | Qt::AlignVCenter, text);

	QList<int> list;
	int i, j, k, x, y;

	y = step;

	for (i = 0; i < 16; i++) {
		uchar *lineByte = image.scanLine(i);
		x = 0;

		for (j = 0; j < 20; j++) {
			uchar tp = lineByte[j];
			QString strBin;

			for (k = 0; k < 8; k++) {
				if (tp & 0x01) {
					strBin += "0";
				} else {
					strBin += "1";
				}

				x += step;
				tp >>= 1;
			}

			bool ok;
			list.append(strBin.toInt(&ok, 2));
		}

		y += step;
	}

	int index = 0;
	QByteArray buffer;

	for (int i = 0; i < 20; i++) {
		for (int j = i; j < 320; j = j + 20) {
			int value = list.at(j);
			buffer.append(value);

			if (value > 0) {
				index = buffer.count();
			}
		}
	}

	buffer.insert(0, (index / 2) + 1);
	return buffer;
}
