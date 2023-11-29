#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "button.h"
#include "label.h"
#include "display.h"
#include "utils.h"
#include "filter.h"

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    struct pult{
        QString        summary_time;
        size_t         step{0};
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
    void play(const size_t& pos);

signals:
     void FileChanged(const QString& path);
     void TextChanged(const Type&, const TextPosition&, const Colour&,const Colour&,const QString& text, const QString& param = QString());
     void Text(const Type& type,const TextPosition&,const text_t&);
private:
    Ui::MainWindow *ui;
    QHash<size_t,QByteArray> d;
    QHash<size_t,pult> pults;
    Filter filter;
private slots:
    void updatePlayer();
    void on_open_sbi_triggered();
    void on_filtr_triggered();
};






#endif // MAINWINDOW_H
