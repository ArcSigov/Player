#include "mainwindow.h"
#include "display.h"
#include "fontreader.h"
#include "page_creator.h"
#include <QApplication>
#include <QDebug>
#include <QThread>





int main(int argc, char *argv[])
{
    auto path = QDir::currentPath();
    QDir::setCurrent(path);
    QApplication a(argc, argv);

    PageCreator   p;
    MainWindow    w(nullptr,&p);
    SreReader     reader(nullptr,ByteSeq::LittleEndian);
    LCDDisplay    display(reader.readFrom("font_mfpu.sre"),&w);


    QObject::connect(&w,&MainWindow::Text,&p,&PageCreator::Text);
    QObject::connect(&p,&PageCreator::TextChanged,&display,&LCDDisplay::read_text);

    w.show();

   return a.exec();
}
