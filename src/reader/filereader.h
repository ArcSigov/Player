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
public slots:
     /** Осуществляет чтение данных в массив байт из файла по заданному пути */
     virtual QByteArray readFrom(const QString& path) = 0;

     /** Осуществляет запись данных в файл по заданному пути из массива байтов */
    virtual void writeTo(const QString& path,const QByteArray& data){
        Q_UNUSED(path)
        Q_UNUSED(data)
    }
     /** Осуществляет запись данных в файл по заданному пути из списка массива байтов */
     virtual void writeTo(const QString& path,const QByteArrayList& data){
        Q_UNUSED(path)
        Q_UNUSED(data)
    }
     /** Осуществляет запись данных в файл по заданному пути из списка строк */
     virtual void writeTo(const QString& path,const QStringList& data){
        Q_UNUSED(path)
        Q_UNUSED(data)
    }
     /** Осуществляет запись данных в файл по заданному пути из строки */
     virtual void writeTo(const QString& path,const QString& data){
        Q_UNUSED(path)
        Q_UNUSED(data)
    }
    virtual void writeTo(const QString& data){
       Q_UNUSED(data)
   }
signals:
    void DataReady(const QByteArray&);
protected:
    QFile* file;
};

#endif // FILEREADER_H
