#ifndef CFGWRITER_H
#define CFGWRITER_H

#include "filereader.h"

class CfgReader : public FileReader
{
public:
    explicit CfgReader(QObject *parent = nullptr);
    ~CfgReader();
    QByteArray readFrom(const QString& path) override;
    void writeTo(const QString& data) override;
};

#endif // CFGWRITER_H
