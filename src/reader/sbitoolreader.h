#ifndef SBITOOLREADER_H
#define SBITOOLREADER_H

#include "filereader.h"
#include <QObject>

class SbiToolReader : public FileReader
{
    Q_OBJECT
public:
    explicit SbiToolReader(QObject *parent = nullptr);    
    QByteArray readFrom(const QString& path) override;
};

#endif // SBITOOLREADER_H
