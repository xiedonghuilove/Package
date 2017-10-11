#include "simple_button.h"

SimpleButton::SimpleButton(const QString &text)
{
    setText(text);
    setFixedSize(65, 50);
    setObjectName("TextButton");

    setFocusPolicy(Qt::NoFocus);
}
