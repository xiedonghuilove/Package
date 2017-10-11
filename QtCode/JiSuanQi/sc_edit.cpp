#include "sc_edit.h"

ScEdit::ScEdit(QWidget *parent) : QLineEdit(parent)
{
    m_evaluator = Evaluator::instance();//初始化计算器
    connect(this,&QLineEdit::textChanged,this,&ScEdit::autoCalculator);
}

void ScEdit::autoCalculator()
{
    const auto str = m_evaluator->autoFix(this->text());//整合一串字符，去除空格等字符

    if(str.isEmpty())
        return;
    m_evaluator->setExpression(str);//设置表达式
    auto quantity = m_evaluator->evalNoAssign();

    if(m_evaluator->error().isEmpty())
    {
        if(quantity.isNan()&&m_evaluator->isUserFunctionAssign())
        {
        }
        else
        {
            auto formatted = NumberFormatter::format(quantity);
            auto message = QString("当前结果:%1").arg(formatted);
            emit autoCalculatorMessage(message);
        }
    }
    else
    {
        emit autoCalculatorError(m_evaluator->error());
    }


}
