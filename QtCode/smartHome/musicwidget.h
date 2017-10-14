#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>

namespace Ui {
class MusicWidget;
}

class MusicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWidget(QWidget *parent = 0);
    ~MusicWidget();

private:
    Ui::MusicWidget *ui;


};

#endif // MUSICWIDGET_H
