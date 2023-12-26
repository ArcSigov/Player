#ifndef MFPUPLAYMANAGER_H
#define MFPUPLAYMANAGER_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include "utils.h"
#include "pult.h"
class MfpuPlayManager : public QObject
{
    Q_OBJECT
public:
    explicit MfpuPlayManager(pult* _pult,QObject *parent = nullptr);
    void play();
signals:
private:
     pult* p;
};

#endif // MFPUPLAYMANAGER_H
