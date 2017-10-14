#include "musicwidget.h"
#include "ui_musicwidget.h"

MusicWidget::MusicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicWidget)
{
    ui->setupUi(this);
}

MusicWidget::~MusicWidget()
{
    delete ui;
}
