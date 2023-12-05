#ifndef MFPUDATAPARSER_H
#define MFPUDATAPARSER_H

#include <QObject>
#include "utils.h"
#include <QVector>
class MfpuDataParser : public QObject
{
    Q_OBJECT
public:
    explicit MfpuDataParser(QObject *parent = nullptr);
public slots:
    void parseData(const QByteArray& d);
signals:
    void dataUpgraded(const QVector<QVector<frame_info>>& frame_data);
private:
    QString find_name(const mfpu_out_sbi_sa_b_t&);
    QVector<QVector<frame_info>> mfpu_frame_data{{},{},{}};
};

#endif // MFPUDATAPARSER_H
