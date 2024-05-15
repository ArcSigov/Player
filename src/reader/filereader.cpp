#include "filereader.h"

FileReader::FileReader(QObject *parent) : QObject(parent)
{
    file = new QFile(this);
}

