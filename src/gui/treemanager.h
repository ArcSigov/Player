#ifndef TREEMANAGER_H
#define TREEMANAGER_H

#include <QObject>
#include <QTreeWidget>
#include "utils.h"

enum columnInfo{
    idMFPU = 0,
    MFPUframe,
    FrameTime
};

class TreeManager : public QObject
{
    Q_OBJECT
public:
    TreeManager(QTreeWidget*, QObject* parent = nullptr);
    void createTree(const QString& treeName, const QVector<frame_info> &mfpu, const bool &type);
    QStringList findInTree(QTreeWidgetItem* item, int column);
private:
    QTreeWidget* tree;
};

#endif // TREEMANAGER_H
