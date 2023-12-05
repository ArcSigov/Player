#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "button.h"
#include "label.h"
#include "display.h"
#include "utils.h"


QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    struct pult{
        QTimer*        ticker;
        QVector<Diod*> diods;
        QHash<size_t,MyButton*> btns;
        LCDDisplay* display;
        size_t         step{0};
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readfonts(const QByteArray& fnt);
public slots:
    void updateData(const QVector<QVector<frame_info>>& data);
signals:
     void FileChanged(const QString& path);
private:
    Ui::MainWindow *ui;
    void play(const size_t& pos);
    QHash<size_t,pult> pults;
    QVector<QVector<frame_info>> mfpu_frame_data;
private slots:
    void updatePlayer();
    void on_open_sbi_triggered();
};






#endif // MAINWINDOW_H
