#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "insertingsettings.h"
#include "page_creator.h"

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

    class MainWindow : public QMainWindow
{
    Q_OBJECT

        public:
                 MainWindow(QWidget *parent = nullptr, PageCreator* p = nullptr);
    ~MainWindow();
             signals:
     void TextChanged(const Type&, const TextPosition&, const Colour&,const Colour&,const QString& text, const QString& param = QString());
     void Text(const Type& type,const TextPosition&,const text_t&);
             private slots:
                 void on_kvs1l_clicked();

             private:
    Ui::MainWindow *ui;
    InsertingSettings* insertSettings;
protected:
    //void mouseDoubleClickEvent(QMouseEvent* ) override;
};






#endif // MAINWINDOW_H
