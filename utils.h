#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
#include <QVector>

enum SymbSize
{
    high,
    medium,
    low
};

enum class Colour
{
    white = 0xc6c6c6,
    blue  = 0xc66f00,
    green = 0x00c600
};

enum class TextAligh
{
    center,
    left,
    right
};

enum TextPosition
{
    HEADER_1,
    HEADER_2,
    KVS1L_1,
    KVS1L_2,
    KVS2L_1,
    KVS2L_2,
    KVS3L_1,
    KVS3L_2,
    KVS4L_1,
    KVS4L_2,
    KVS5L_1,
    KVS5L_2,
    KVS1R_1,
    KVS1R_2,
    KVS2R_1,
    KVS2R_2,
    KVS3R_1,
    KVS3R_2,
    KVS4R_1,
    KVS4R_2,
    KVS5R_1,
    KVS5R_2
};

enum Type
{
    Button,
    String,
    Switcher,
    Header
};

struct text_t
{
    QStringList      text;      //список текста для этой строки (будет на экране последовательно рисоваться)
    QVector<Colour>  colour;    //список цветов этого текста    (дисплей будет красить его по позициям листа)
};

#endif // UTILS_H
