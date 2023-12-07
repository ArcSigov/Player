#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "button.h"
#include "label.h"
#include "display.h"
#include "utils.h"
#include <QThread>
#include <QMutex>
#include <QTreeWidgetItem>
#include "treemanager.h"
#include <QTextCodec>
QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct pult{
    QTimer*        ticker;
    QVector<Diod*> diods;
    QHash<size_t,MyButton*> btns;
    LCDDisplay* display;
    QSlider*    step;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString cfg;
    QHash<size_t,pult> pults;
    QVector<QVector<frame_info>> mfpu_frame_data{{},{},{}};
    TreeManager* treemanager;
    QTextCodec* codec;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readfonts(const QByteArray& fnt);
    void readcfg(const QByteArray& cfg);
    void defaultShow();
public slots:
    void updateData(const QVector<QVector<frame_info>>& data);
signals:
     void FileChanged(const QString& path);
private:
    Ui::MainWindow *ui;
    void play(const size_t& pos);
private slots:
    void updatePlayer();
    void on_open_sbi_triggered();
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    frame_info initDefaultFrame();
};






#endif // MAINWINDOW_H
