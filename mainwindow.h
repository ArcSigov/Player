#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
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
        QString        summary_time;
        size_t         step;
        QTimer*        ticker;
        QVector<Diod*> diods;
        QHash<size_t,MyButton*> btns;
        LCDDisplay* display;
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setbytes(const QByteArray& _d);
    void readfonts(const QByteArray& fnt);
signals:
     void FileChanged(const QString& path);
     void TextChanged(const Type&, const TextPosition&, const Colour&,const Colour&,const QString& text, const QString& param = QString());
     void Text(const Type& type,const TextPosition&,const text_t&);
public slots:
     void play_p1();
     void play_p2();
     void play_p3();
     void updateStepP1(int pos);
     void updateStepP2(int pos);
     void updateStepP3(int pos);
private:
    Ui::MainWindow *ui;
    QHash<size_t,QByteArray> d;
    size_t pos = 0;
    QHash<size_t,pult> pults;
protected:
    //void mouseDoubleClickEvent(QMouseEvent* ) override;
private slots:
    void on_open_sbi_triggered();
    void on_play_clicked();
    void on_pause_clicked();
    void on_play_2_clicked();
    void on_pause_2_clicked();
    void on_play_3_clicked();
    void on_pause_3_clicked();
};






#endif // MAINWINDOW_H
