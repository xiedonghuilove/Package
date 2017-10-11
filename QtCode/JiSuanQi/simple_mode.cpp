#include "simple_mode.h"

typedef Quantity::Format Format;

SimpleMode::SimpleMode(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    editText = new SimpleEdit();

    clearButton = new SimpleButton("AC");
    backButton = new SimpleButton("←");
    divButton = new SimpleButton("÷");
    multButton = new SimpleButton("×");

    sevenButton = new SimpleButton("7");
    eightButton = new SimpleButton("8");
    nineButton = new SimpleButton("9");
    minusButton = new SimpleButton("－");

    fourButton = new SimpleButton("4");
    fiveButton = new SimpleButton("5");
    sixButton = new SimpleButton("6");
    plusButton = new SimpleButton("＋");

    oneButton = new SimpleButton("1");
    twoButton = new SimpleButton("2");
    threeButton = new SimpleButton("3");

    zeroButton = new SimpleButton("0");
    pointButton = new SimpleButton(".");
    equalButton = new SimpleButton("＝");

    m_evaluator = Evaluator::instance();//实例化计算器(类似初始化)

    layout->addWidget(editText, 1, 0, 1, 4);

    layout->addWidget(clearButton, 2, 0);
    layout->addWidget(backButton, 2, 1);
    layout->addWidget(divButton, 2, 2);
    layout->addWidget(multButton, 2, 3);

    layout->addWidget(sevenButton, 3, 0);
    layout->addWidget(eightButton, 3, 1);
    layout->addWidget(nineButton, 3, 2);
    layout->addWidget(minusButton, 3, 3);

    layout->addWidget(fourButton, 4, 0);
    layout->addWidget(fiveButton, 4, 1);
    layout->addWidget(sixButton, 4, 2);
    layout->addWidget(plusButton, 4, 3);

    layout->addWidget(oneButton, 5, 0);
    layout->addWidget(twoButton, 5, 1);
    layout->addWidget(threeButton, 5, 2);

    layout->addWidget(zeroButton, 6, 0, 1, 2);
    layout->addWidget(pointButton, 6, 2);
    layout->addWidget(equalButton, 5, 3, 2, 2);

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(on_clear_button_clicked()));
    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(on_back_button_clicked()));
    connect(divButton, SIGNAL(clicked(bool)), this, SLOT(on_div_button_clicked()));
    connect(multButton, SIGNAL(clicked(bool)), this, SLOT(on_mult_button_clicked()));

    connect(minusButton, SIGNAL(clicked(bool)), this, SLOT(on_minus_button_clicked()));
    connect(plusButton, SIGNAL(clicked(bool)), this, SLOT(on_plus_button_clicked()));
    connect(pointButton, SIGNAL(clicked(bool)), this, SLOT(on_point_button_clicked()));
    connect(sevenButton, SIGNAL(clicked(bool)), this, SLOT(on_seven_button_clicked()));
    connect(eightButton, SIGNAL(clicked(bool)), this, SLOT(on_eight_button_clicked()));
    connect(nineButton, SIGNAL(clicked(bool)), this, SLOT(on_nine_button_clicked()));
    connect(fourButton, SIGNAL(clicked(bool)), this, SLOT(on_four_button_clicked()));
    connect(fiveButton, SIGNAL(clicked(bool)), this, SLOT(on_five_button_clicked()));
    connect(sixButton, SIGNAL(clicked(bool)), this, SLOT(on_six_button_clicked()));
    connect(oneButton, SIGNAL(clicked(bool)), this, SLOT(on_one_button_clicked()));
    connect(twoButton, SIGNAL(clicked(bool)), this, SLOT(on_two_button_clicked()));
    connect(threeButton, SIGNAL(clicked(bool)), this, SLOT(on_three_button_clicked()));
    connect(zeroButton, SIGNAL(clicked(bool)), this, SLOT(on_zero_button_clicked()));
    connect(equalButton, SIGNAL(clicked(bool)), this, SLOT(on_equal_button_clicked()));

    initUI();
}
void SimpleMode::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        equalButton->clicked(true);
}

void SimpleMode::initUI()
{
    editText->setObjectName("SimpleEdit");
    editText->setFixedHeight(80);//设置高度
    editText->setAlignment(Qt::AlignRight);//右对齐
    editText->setFocus();

    equalButton->setFixedHeight(equalButton->height()*2);
    zeroButton->setFixedWidth(zeroButton->width()*2);

    equalButton->setObjectName("TextButtonIs");
    clearButton->setStyleSheet("QPushButton { color: #2CA7F8; }");

}
//清空
void SimpleMode::on_clear_button_clicked()
{
    editText->clear();
    editText->setFocus();
}
//删除
void SimpleMode::on_back_button_clicked()
{
    editText->setFocus();

    if (editText->text().isEmpty())
        return;

    editText->backspace();//删除文本光标左侧的字符
}
//数字按钮点击
void SimpleMode::on_number_button_clicked(const QString &text)
{
    editText->insert(text);//插入
    editText->setFocus();
}

void SimpleMode::on_div_button_clicked()
{
    on_symbol_button_clicked("÷");
}
void SimpleMode::on_mult_button_clicked()
{
    on_symbol_button_clicked("×");
}
void SimpleMode::on_seven_button_clicked()
{
    on_number_button_clicked("7");
}

void SimpleMode::on_eight_button_clicked()
{
    on_number_button_clicked("8");
}

void SimpleMode::on_nine_button_clicked()
{
    on_number_button_clicked("9");
}
void SimpleMode::on_minus_button_clicked()
{
    if (editText->text().isEmpty())
    {
        editText->insert("-");
        return;
    }

    on_symbol_button_clicked("-");
}

void SimpleMode::on_four_button_clicked()
{
    on_number_button_clicked("4");
}

void SimpleMode::on_five_button_clicked()
{
    on_number_button_clicked("5");
}

void SimpleMode::on_six_button_clicked()
{
    on_number_button_clicked("6");
}

void SimpleMode::on_plus_button_clicked()
{
    on_symbol_button_clicked("+");
}

void SimpleMode::on_one_button_clicked()
{
    on_number_button_clicked("1");
}

void SimpleMode::on_two_button_clicked()
{
    on_number_button_clicked("2");
}

void SimpleMode::on_three_button_clicked()
{
    on_number_button_clicked("3");
}

void SimpleMode::on_zero_button_clicked()
{
    on_number_button_clicked("0");
}

void SimpleMode::on_point_button_clicked()
{
    editText->insert(".");
    editText->setFocus();
}

//插入符号
void SimpleMode::on_symbol_button_clicked(const QString &text)
{
    if (editText->text().isEmpty())
        editText->insert("0");

    editText->insert(text);
    editText->setFocus();
}
//计算结果
void SimpleMode::on_equal_button_clicked()
{
    if (editText->text().isEmpty())
        return;

    m_evaluator->initializeBuiltInVariables();//初始化内置变量
    m_evaluator->autoFix(editText->text());//将一整串的字符处理，去除空白等等
    m_evaluator->setExpression(editText->text().replace("×", "*").replace("÷", "/"));//设置表达式

    Quantity rn = m_evaluator->evalUpdateAns();
    QString result = DMath::format(rn, Format::Fixed());

    editText->setText(result);//计算结果
    editText->setFocus();
}
