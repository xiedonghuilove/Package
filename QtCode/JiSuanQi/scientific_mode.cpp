#include "scientific_mode.h"
#include <QToolTip>

typedef Quantity::Format Format;//重声明

ScientificMode::ScientificMode(QWidget *parent) : QWidget(parent)
{
    m_evaluator = Evaluator::instance();//初始化

    layout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout(this);
    layout1 = new QHBoxLayout(this);
    layout2 = new QHBoxLayout(this);
    layout3 = new QHBoxLayout(this);
    layout4 = new QHBoxLayout(this);

    state = new QLabel(this);
    display = new ResultDisplay(this);
    editor = new ScEdit(this);


    //QToolTip --> 工具提示类
    state->setPalette(QToolTip::palette());
    state->setAutoFillBackground(true);//自动填充背景
    state->setFrameShape(QFrame::Box);//该属性保存框架样式的框架形状值。QFrame围绕其内容绘制一个框
    state->hide();//隐藏窗口小部件

    layout1->setSpacing(0);
    layout2->setSpacing(0);
    layout3->setSpacing(0);
    layout4->setSpacing(0);

    layout1->setMargin(0);
    layout2->setMargin(0);
    layout3->setMargin(0);
    layout4->setMargin(0);

    layout->setSpacing(0);
    layout->setMargin(0);

    layout->setContentsMargins(0, 0, 0, 0);

    btn7 = new ScButton("7");
        btn8 = new ScButton("8");
        btn9 = new ScButton("9");
        btnDiv = new ScButton("÷");
        btnC = new ScButton("C");
        btnRoot = new ScButton("√");
        btnP = new ScButton("π");
        btnExp = new ScButton("exp");
        btnLn = new ScButton("ln");
        btnBin = new ScButton("Bin");//二进制

        btn4 = new ScButton("4");
        btn5 = new ScButton("5");
        btn6 = new ScButton("6");
        btnMult = new ScButton("×");
        btnE = new ScButton("E");
        btnS = new ScButton("^");
        btnAns = new ScButton("ans");
        btnSin = new ScButton("sin");
        btnArcsin = new ScButton("arcsin");
        btnOct = new ScButton("Oct");//八进制

        btn1 = new ScButton("1");
        btn2 = new ScButton("2");
        btn3 = new ScButton("3");
        btnMinus = new ScButton("－");
        btnLeft = new ScButton("(");
        btnRight = new ScButton(")");
        btnX = new ScButton("x");
        btnCos = new ScButton("cos");
        btnArccos = new ScButton("arccos");
        btnDec = new ScButton("Dec");//十进制

        btn0 = new ScButton("0");
        btnPoint = new ScButton(".");
        btnIs = new ScButton("＝");
        btnPlus = new ScButton("＋");
        btnMod = new ScButton("%");
        btnG = new ScButton("!");
        btnXis = new ScButton("x=");
        btnTan = new ScButton("tan");
        btnArctan = new ScButton("arctan");
        btnHex = new ScButton("Hex");

        topLayout->addWidget(editor);

        layout1->addWidget(btn7);
        layout1->addWidget(btn8);
        layout1->addWidget(btn9);
        layout1->addWidget(btnDiv);
        layout1->addWidget(btnC);
        layout1->addWidget(btnRoot);
        layout1->addWidget(btnP);
        layout1->addWidget(btnExp);
        layout1->addWidget(btnLn);
        layout1->addWidget(btnBin);//二进制

        layout2->addWidget(btn4);
        layout2->addWidget(btn5);
        layout2->addWidget(btn6);
        layout2->addWidget(btnMult);
        layout2->addWidget(btnE);
        layout2->addWidget(btnS);
        layout2->addWidget(btnAns);
        layout2->addWidget(btnSin);
        layout2->addWidget(btnArcsin);
        layout2->addWidget(btnOct);//八进制

        layout3->addWidget(btn1);
        layout3->addWidget(btn2);
        layout3->addWidget(btn3);
        layout3->addWidget(btnMinus);
        layout3->addWidget(btnLeft);
        layout3->addWidget(btnRight);
        layout3->addWidget(btnX);
        layout3->addWidget(btnCos);
        layout3->addWidget(btnArccos);
        layout3->addWidget(btnDec);//十进制

        layout4->addWidget(btn0);
        layout4->addWidget(btnPoint);
        layout4->addWidget(btnIs);
        layout4->addWidget(btnPlus);
        layout4->addWidget(btnMod);
        layout4->addWidget(btnG);
        layout4->addWidget(btnXis);
        layout4->addWidget(btnTan);
        layout4->addWidget(btnArctan);
        layout4->addWidget(btnHex);//十六进制

        layout->addWidget(display);
        layout->addLayout(topLayout);
        layout->addLayout(layout1);
        layout->addLayout(layout2);
        layout->addLayout(layout3);
        layout->addLayout(layout4);

        layout->setContentsMargins(0, 0, 0, 0);

        setLayout(layout);

        btnC->setStyleSheet("QPushButton { color: #2CA7F8; }");

        connect(display, &QPlainTextEdit::selectionChanged, this, [=] {
            editor->setFocus();
        });

        connect(editor, SIGNAL(autoCalculatorMessage(QString)), this, SLOT(showStateLabel(QString)));//自动计算警告
        connect(editor, SIGNAL(autoCalculatorError(QString)), this, SLOT(showStateLabel(QString)));//自动计算错误
        connect(editor, SIGNAL(textChanged(QString)), this, SLOT(lineEditTextChanged(QString)));
        connect(btnIs, SIGNAL(clicked(bool)), this, SLOT(on_equal_button_clicked()));

        connect(btn7, &QPushButton::clicked, this, [=]{
            editor->insert("7");
        });
        connect(btn8, &QPushButton::clicked, this, [=]{
            editor->insert("8");
        });
        connect(btn9, &QPushButton::clicked, this, [=]{
            editor->insert("9");
        });
        connect(btnDiv, &QPushButton::clicked, this, [=]{
            editor->insert("÷");
        });
        connect(btnC, &QPushButton::clicked, this, [=]{
            editor->clear();
        });
        connect(btnRoot, &QPushButton::clicked, this, [=]{
            editor->insert("sqrt(");
        });
        connect(btnP, &QPushButton::clicked, this, [=]{
            editor->insert("pi");
        });
        connect(btnExp, &QPushButton::clicked, this, [=]{
            editor->insert("exp(");
        });
        connect(btnLn, &QPushButton::clicked, this, [=]{
            editor->insert("ln(");
        });

        connect(btn4, &QPushButton::clicked, this, [=]{
            editor->insert("4");
        });
        connect(btn5, &QPushButton::clicked, this, [=]{
            editor->insert("5");
        });
        connect(btn6, &QPushButton::clicked, this, [=]{
            editor->insert("6");
        });
        connect(btnMult, &QPushButton::clicked, this, [=]{
            editor->insert("×");
        });
        connect(btnE, &QPushButton::clicked, this, [=]{
            editor->insert("e");
        });
        connect(btnS, &QPushButton::clicked, this, [=]{
            editor->insert("^");
        });
        connect(btnAns, &QPushButton::clicked, this, [=]{
            editor->insert("ans");
        });
        connect(btnSin, &QPushButton::clicked, this, [=]{
            editor->insert("sin(");
        });
        connect(btnArcsin, &QPushButton::clicked, this, [=]{
            editor->insert("arcsin(");
        });

        connect(btn1, &QPushButton::clicked, this, [=]{
            editor->insert("1");
        });
        connect(btn2, &QPushButton::clicked, this, [=]{
            editor->insert("2");
        });
        connect(btn3, &QPushButton::clicked, this, [=]{
            editor->insert("3");
        });
        connect(btnMinus, &QPushButton::clicked, this, [=]{
            editor->insert("-");
        });
        connect(btnLeft, &QPushButton::clicked, this, [=]{
            editor->insert("(");
        });
        connect(btnRight, &QPushButton::clicked, this, [=]{
            editor->insert(")");
        });
        connect(btnX, &QPushButton::clicked, this, [=]{
            editor->insert("x");
        });
        connect(btnCos, &QPushButton::clicked, this, [=]{
            editor->insert("cos(");
        });
        connect(btnArccos, &QPushButton::clicked, this, [=]{
            editor->insert("arccos(");
        });

        connect(btn0, &QPushButton::clicked, this, [=]{
            editor->insert("0");
        });
        connect(btnPoint, &QPushButton::clicked, this, [=]{
            editor->insert(".");
        });
        connect(btnPlus, &QPushButton::clicked, this, [=]{
            editor->insert("+");
        });
        connect(btnMod, &QPushButton::clicked, this, [=]{
            editor->insert("%");
        });
        connect(btnG, &QPushButton::clicked, this, [=]{
            editor->insert("!");
        });
        connect(btnXis, &QPushButton::clicked, this, [=]{
            editor->insert("x=");
        });
        connect(btnTan, &QPushButton::clicked, this, [=]{
            editor->insert("tan(");
        });
        connect(btnArctan, &QPushButton::clicked, this, [=]{
            editor->insert("arctan(");
        });

        //增加进制之间的转换
        connect(btnBin, &QPushButton::clicked, this, [=]{
            editor->insert("bin(");
        });
        connect(btnOct, &QPushButton::clicked, this, [=]{
            editor->insert("oct(");
        });
        connect(btnDec, &QPushButton::clicked, this, [=]{
            editor->insert("dec(");
        });
        connect(btnHex, &QPushButton::clicked, this, [=]{
            editor->insert("hex(");
        });
}

//等于按钮
void ScientificMode::on_equal_button_clicked()
{
    if (editor->text().isEmpty())
        return;

    m_evaluator->initializeBuiltInVariables();
    m_evaluator->autoFix(editor->text());
    m_evaluator->setExpression(editor->text().replace("×", "*").replace("÷", "/"));

    Quantity rn = m_evaluator->evalUpdateAns();
    QString result = DMath::format(rn, Format::Fixed());

    display->append(editor->text());
    display->append(QString("= %1").arg(result));
    display->append(QLatin1String(""));

    editor->setText(result);
    display->moveCursor(QTextCursor::End);

    editor->clear();
    editor->setFocus();
}

//重写键盘
void ScientificMode::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        btnIs->clicked(true);
    }
}
//显示状态标签
void ScientificMode::showStateLabel(const QString &text)
{
    state->setText(text);
    state->adjustSize();
    state->show();
    state->raise();

    const int height = state->height();
    QPoint pos= mapFromGlobal(editor->mapToGlobal(QPoint(0, -height)));
    state->move(pos);
}
//文本改变
void ScientificMode::lineEditTextChanged(const QString &text)
{
    if (text.isEmpty()) {
        state->hide();
    }
}

