#include "treemanager.h"
#include <QDebug>


TreeManager::TreeManager(QTreeWidget* _tree, QObject* parent) : QObject(parent), tree(_tree)
{


}

void TreeManager::createTree(const QString& treeName,const QVector<frame_info> &mfpu)
{
    if (tree && !tree->findItems(treeName,Qt::MatchStartsWith).size())
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(100);
        item->setText(idMFPU,treeName);
        for (const auto& frame:mfpu)
        {
            bool finded = false;
            QTreeWidgetItem* findedChild;
            for (auto i = 0 ; i < item->childCount();i++)
            {
                findedChild = item->child(i);
                if (findedChild->text(MFPUframe) == frame.name)
                {
                    finded = true;
                    break;
                }
            }
            if (!finded)
            {
                QTreeWidgetItem* child = new QTreeWidgetItem(101);
                child->setText(MFPUframe,frame.name);
                child->setText(FrameTime,frame.time);
                item->addChild(child);
            }
            else
            {
                QTreeWidgetItem* child = new QTreeWidgetItem(102);
                child->setText(FrameTime,frame.time);
                findedChild->addChild(child);
            }
        }
        tree->addTopLevelItem(item);
    }
}



QStringList TreeManager::findInTree(QTreeWidgetItem* item, int column)
{
    if (column == idMFPU)
        return {};

    QStringList out;
    switch(item->type())
    {
        case 102:
            out.push_back(item->parent()->parent()->text(idMFPU));
            out.push_back(item->parent()->text(MFPUframe));
            out.push_back(item->text(FrameTime));
        break;
        case 101:
            out.push_back(item->parent()->text(idMFPU));
            out.push_back(item->text(MFPUframe));
            out.push_back(item->text(FrameTime));
        break;
        case 100:
        default:
        break;
    }
    return out;
}
