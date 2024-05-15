#ifndef FONTREADER_H
#define FONTREADER_H

#include <QObject>
#include "filereader.h"

enum class ByteSeq
{
    LittleEndian,
    BigEndian
};

class FontReader : public FileReader
{
    Q_OBJECT
        public:
        explicit FontReader(QObject *parent = nullptr, const ByteSeq& seq = ByteSeq::LittleEndian);

            /** Осуществляет чтение данных в массив байт из файла по заданному пути */
            QByteArray readFrom(const QString& path = QDir::currentPath()+"/font_mfpu.sre")   override;

signals:
private:
    ByteSeq sequence;
};

#endif // FONTREADER_H
