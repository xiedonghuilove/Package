#include "sc_button.h"

ScButton::ScButton(const QString &text)
{
    setText(text);
    setFixedHeight(45);//设置高度45
    setObjectName("TextButton");

    setFocusPolicy(Qt::NoFocus);
}
