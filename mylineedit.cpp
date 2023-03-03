#include "mylineedit.h"
#include <QDebug>
#include <QMouseEvent>

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void MyLineEdit::mousePressEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
        emit currentFieldEnabled(this);
}

void MyLineEdit::InsertSymbol(const QString& symb)
{
    auto text = this->text();
    setText(text+symb);
    update();
}
