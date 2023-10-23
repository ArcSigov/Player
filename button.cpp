#include "button.h"
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget* parent) : QPushButton(parent)
{
    setStyle(btnstyle::def);
}


void MyButton::setStyle(const btnstyle& style)
{
    switch (style)
    {
    case btnstyle::def:
        setStyleSheet(QString());
        break;
    case btnstyle::black_background:
        setStyleSheet("QPushButton{background: black;" "border: 1px solid white;}"
                      "QPushButton:hover{background: white; color:white}");
        break;
    case btnstyle::white_text_black_background:
        setStyleSheet("QPushButton{color: white;background: black; border: 1px solid white;}"
                      "QPushButton:hover{color: black;background: white;}");
        break;
    case btnstyle::clicked:
        setStyleSheet("QPushButton{color: black;background: white;}");
        break;
    default:break;
    }
}

