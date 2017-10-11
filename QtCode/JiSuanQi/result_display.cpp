#include "result_display.h"

ResultDisplay::ResultDisplay(QWidget *parent) : QPlainTextEdit(parent)
{
    setViewportMargins(0,0,0,0);//设置间距
    setBackgroundRole(QPalette::Base);//主要用作文本输入小部件的背景颜色，但也可用于其他绘画 - 例如组合框下拉列表和工具栏手柄的背景。 它通常是白色或另一种浅色。
    setLayoutDirection(Qt::LeftToRight);//从左到右
    setReadOnly(true);

    setWordWrapMode(QTextOption::WrapAnywhere);//文本可以包裹在一行上的任意一点，即使它出现在一个单词的中间。

    QFont font;
    font.setFamily("Noto Mono");
    font.setPointSize(15);
    setFont(font);

    m_count = 0;
}

void ResultDisplay::append(const QString &text)
{
    ++m_count;
    appendPlainText(text);//插入字符
}
