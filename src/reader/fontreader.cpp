#include "fontreader.h"
#include <QTextStream>

FontReader::FontReader(QObject *parent,  const ByteSeq& seq) : FileReader(parent), sequence(seq)
{


}

/** Осуществляет чтение данных sre файла в порядке BE или LE в массив байт из файла по заданному пути */
QByteArray FontReader::readFrom(const QString& path)
{
    file->setFileName(path);
    QByteArray  data;
    if (file->open(QIODevice::ReadOnly))
    {
        QTextStream out(file);
        while (!out.atEnd())
        {
            auto line = out.readLine();
            if (line.contains("S3"))
            {
                auto bytes_count = QString(line.cbegin()+2,2).toUInt(nullptr,16) - 5;
                for (auto pos = 0ull; pos < bytes_count * 2; pos+=2)
                {
                    if (sequence == ByteSeq::LittleEndian)
                        data.push_back(QString(line.cbegin()+12+pos,2).toUInt(nullptr,16));
                    else
                        data.push_front(QString(line.cbegin()+12+pos,2).toUInt(nullptr,16));
                }
            }
        }
        file->close();
    }
    return data;
}



