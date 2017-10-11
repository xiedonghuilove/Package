#include "simple_edit.h"

SimpleEdit::SimpleEdit(QWidget *parent) : QLineEdit(parent)
{
    connect(this,&QLineEdit::textChanged,this,&SimpleEdit::changeFontSize);
    //改变文本-->改变字体大小。
}

void SimpleEdit::changeFontSize()
{
    QFont font;

    if (text().size() <= 10) {
        font.setPointSize(20);
    } else if (text().size() > 10) {
        font.setPointSize(15);
    } else if (text().size() > 15) {
        font.setPointSize(10);
    }

    this->setFont(font);
}
