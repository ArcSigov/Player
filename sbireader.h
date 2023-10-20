#ifndef SBIREADER_H
#define SBIREADER_H

#include "filereader.h"

class SbiRSReader : public FileReader
{
    Q_OBJECT
public:
    explicit SbiRSReader(QObject *parent = nullptr);
    QByteArray readFrom(const QString& path) override;
signals:

};

#endif // SBIREADER_H
