#include "mfpudataparser.h"
#include <QDateTime>
#include <QDebug>
#include <QTextCodec>


MfpuDataParser::MfpuDataParser(QObject *parent)
    : QObject{parent}
{

}

void MfpuDataParser::parseData(const QByteArray& d)
{
    auto _d = d;
    _d.remove(0,8);
    auto num = d[0];
    for (auto i = 0 ; i < _d.size(); i+=sizeof(mfpu_out_b_t))
    {
        auto data = (mfpu_out_b_t*)(_d.data()+i);
        frame_info frame;
        frame.time = QDateTime::fromMSecsSinceEpoch(data->time).time().toString();
        memcpy(&frame.info,&data->data,sizeof(mfpu_out_data_b_t));
        for (auto j = 0 ; j < 12 ; j++)
        {
            if (frame.info.data[j].id_b.line_number == 1)
            {
                frame.name = find_name(frame.info.data[j]);
                break;
            }
        }
        mfpu_frame_data[num-1].push_back(frame);
    }
    emit dataUpgraded(mfpu_frame_data);
}

QString MfpuDataParser::find_name(const mfpu_out_sbi_sa_b_t& data)
{
    QString out;
    QTextCodec* codec = QTextCodec::codecForName("CP1251");
    for (auto i=0 ; i<28; i++)
    {
        if (!(data.symbols_b[i].code >= 0x80 && data.symbols_b[i].code <= 0x9a))
        {
         if (data.symbols_b[i].forecolor == 6 || data.symbols_b[i].forecolor == 2)
               out.push_back(codec->toUnicode((char*)&data.symbols_b[i],1));
         else if (data.symbols_b[i].forecolor == 0)
               out.push_back(" ");
        }
    }

    auto i = 0;
    for (i = 0; i < out.size(); i++)
        if (out[i] != ' ')
            break;
    out = QString(out.data()+i,out.size()-i);

    for (i=out.size()-1; i > 0;i--)
        if (out[i]!=' ')
            break;
    out.remove(i+1,out.size()-i);
    return out;
}
