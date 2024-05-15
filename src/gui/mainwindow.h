#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QVector>
#include <QTextCodec>
#include "utils.h"
#include "treemanager.h"
#include "about.h"
#include "settings.h"
#include <QGroupBox>
#include "pult.h"


QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString cfg;
    QHash<size_t,pult> pults;
    TreeManager* treemanager;
    QTextCodec* codec;
    About about;
    Settings setts;
    settings s;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readfonts(const QByteArray& fnt);
    void readcfg(const QByteArray& cfg);
    void defaultShow();
public slots:
    void updateData(const QVector<QVector<frame_info>>& data);
    void readSettings(const settings& _s);
signals:
     void FileChanged(const QString& path);
     void enableSetMfpu(const size_t& num);
private:
    Ui::MainWindow *ui;
    void play(const size_t& pos);
    QVector<bool> synchronize();
private slots:
    void updatePlayer();
    void on_open_sbi_triggered();
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    frame_info initDefaultFrame();
};






#endif // MAINWINDOW_H
