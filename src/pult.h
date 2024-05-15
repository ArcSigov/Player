#ifndef PULT_H
#define PULT_H

#include "display.h"
#include "label.h"
#include "button.h"
#include <QPushButton>
#include <QSlider>
#include <QGroupBox>

struct playerBar{
    MyButton* play;
    MyButton* stop;
    MyButton* next;
    MyButton* back;
    QSlider*  step;
    QGroupBox* bar;
};

struct pult{
    size_t                     master_num;
    QTimer*                    ticker;
    QVector<Diod*>             diods;
    QHash<size_t,MyButton*>    btns;
    LCDDisplay*                display;
    QVector<frame_info>        frame_data{};
    playerBar                  player;
};

#endif // PULT_H
