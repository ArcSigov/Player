#ifndef MFPUPLAYMANAGER_H
#define MFPUPLAYMANAGER_H

#include <QObject>
#include <QMutex>
class MfpuPlayManager : public QObject
{
    Q_OBJECT
public:
    explicit MfpuPlayManager(QObject *parent = nullptr);
    void play();
signals:

};

#endif // MFPUPLAYMANAGER_H
