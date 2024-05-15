#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QObject>

enum class btnstyle
{
    def,
    black_background,
    white_text_black_background,
    clicked
};

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QWidget* parent = nullptr);
    void setStyle(const btnstyle& colour);
};

#endif // BUTTON_H
