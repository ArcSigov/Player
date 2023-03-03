#ifndef FONTREADER_H
#define FONTREADER_H

#include <QObject>
#include "filereader.h"

enum class ByteSeq
{
    LittleEndian,
    BigEndian
};

class SreReader : public FileReader
{
    Q_OBJECT
        public:
        explicit SreReader(QObject *parent = nullptr, const ByteSeq& seq = ByteSeq::LittleEndian);

            /** Осуществляет чтение данных в массив байт из файла по заданному пути */
            QByteArray readFrom(const QString& path = QDir::currentPath()+"/font_mfpu.sre")   override;

            /** Осуществляет запись данных в файл по заданному пути из массива байтов */
            void writeTo(const QString& path,const QByteArray& data)     override;

            /** Осуществляет запись данных в файл по заданному пути из списка массива байтов */
            void writeTo(const QString& path,const QByteArrayList& data) override;

            /** Осуществляет запись данных в файл по заданному пути из списка строк */
            void writeTo(const QString& path,const QStringList& data)    override;

            /** Осуществляет запись данных в файл по заданному пути из строки */
            void writeTo(const QString& path,const QString& data)        override;

signals:
private:
    ByteSeq sequence;
};

#endif // FONTREADER_H
