#include "sbitoolreader.h"
#include <QDataStream>
#include <QDebug>

SbiToolReader::SbiToolReader(QObject *parent)
    : FileReader{parent}
{

}


QByteArray SbiToolReader::readFrom(const QString& path){
    size_t mfpu_num = 0;
    if (path.contains("mfpu_11"))
        mfpu_num = 1;
    else if (path.contains("mfpu_12"))
        mfpu_num = 2;
    else if (path.contains("mfpu_13"))
        mfpu_num = 3;
    else
        return {};

    QByteArray out;
    file->setFileName(path);
    if (file->open(QIODevice::ReadOnly)){
        out.append(file->size(),0);
        QDataStream in(file);
        in.readRawData(out.data(),out.size());
        file->close();
    }
    out.prepend((char*)&mfpu_num, sizeof(size_t));
    emit DataReady(out);
    return out;
}
