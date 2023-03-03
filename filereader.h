#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QDir>

class FileReader : public QObject
{
    Q_OBJECT
public:
     explicit FileReader(QObject *parent = nullptr);

     /** Осуществляет чтение данных в массив байт из файла по заданному пути */
     virtual QByteArray readFrom(const QString& path)                     = 0;

     /** Осуществляет запись данных в файл по заданному пути из массива байтов */
     virtual void writeTo(const QString& path,const QByteArray& data)     = 0;

     /** Осуществляет запись данных в файл по заданному пути из списка массива байтов */
     virtual void writeTo(const QString& path,const QByteArrayList& data) = 0;

     /** Осуществляет запись данных в файл по заданному пути из списка строк */
     virtual void writeTo(const QString& path,const QStringList& data)    = 0;

     /** Осуществляет запись данных в файл по заданному пути из строки */
     virtual void writeTo(const QString& path,const QString& data)        = 0;
signals:
protected:
    QFile* file;
};

#endif // FILEREADER_H
