#include "sbireader.h"
#include <QTextStream>
SbiRSReader::SbiRSReader(QObject *parent)
    : FileReader(parent)
{

}

QByteArray SbiRSReader::readFrom(const QString& path)
{
    auto mfpu_num = 1ull;
    file->setFileName(path);
    if (file->open(QIODevice::ReadOnly))
    {
        QByteArray out;
        QTextStream d(file);
        auto finded = false;
        while (!d.atEnd())
        {
            auto l = d.readLine();
            if (l.contains("Rec.packet len=776"))
            {
                finded = true;
                continue;
            }
            if (finded)
            {
                out.append((char*)&mfpu_num, sizeof(size_t));
                for (auto pos = 64; pos < l.length();pos+=2)
                   out.push_back(QString(l.cbegin()+pos,2).toUInt(nullptr,16));
                finded = false;
            }
        }
        file->close();
        out.prepend((char*)&mfpu_num, sizeof(size_t));
        emit DataReady(out);
        return out;
    }
    return {};
}
