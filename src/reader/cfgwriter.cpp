#include "cfgwriter.h"

CfgReader::CfgReader(QObject *parent)
    : FileReader{parent}
{

}

CfgReader::~CfgReader()
{
    file->close();
}

QByteArray CfgReader::readFrom(const QString& path)
{
    file->setFileName(path);
    QString out;
    if (file->open(QIODevice::ReadWrite))
    {
        out = file->readLine();
    }
    return QByteArray(out.toStdString().c_str());
}

void CfgReader::writeTo(const QString& data)
{
    file->write(data.toStdString().c_str());
}
