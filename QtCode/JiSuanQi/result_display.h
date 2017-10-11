#ifndef RESULTDISPLAY_H
#define RESULTDISPLAY_H

#include <QPlainTextEdit>

class ResultDisplay : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ResultDisplay(QWidget *parent = 0);

    void append(const QString &text);
private:
    int m_count;

};

#endif // RESULTDISPLAY_H
