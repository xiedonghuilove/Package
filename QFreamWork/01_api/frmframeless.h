#ifndef FRMFRAMELESS_H
#define FRMFRAMELESS_H

#include <QWidget>

namespace Ui {
class frmFrameless;
}

class frmFrameless : public QWidget
{
    Q_OBJECT

public:
    explicit frmFrameless(QWidget *parent = 0);
    ~frmFrameless();

private:
    Ui::frmFrameless *ui;
};

#endif // FRMFRAMELESS_H
