#ifndef SIMPLEBUTTON_H
#define SIMPLEBUTTON_H

#include <QPushButton>

class SimpleButton : public QPushButton
{
    Q_OBJECT
public:
    SimpleButton(const QString &text);

};

#endif // SIMPLEBUTTON_H
