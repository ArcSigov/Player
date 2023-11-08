#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "fontreader.h"
#include "sbireader.h"
#include "sbitoolreader.h"


int main(int argc, char *argv[])
{
    auto path = QDir::currentPath();
    QDir::setCurrent(path);
    QApplication a(argc, argv);


    MainWindow    w;
    FontReader     reader(nullptr,ByteSeq::LittleEndian);
    SbiRSReader   RsReader;
    SbiToolReader toolreader;

    w.readfonts(reader.readFrom("font_mfpu.sre"));
    w.show();

    QObject::connect(&w,&MainWindow::FileChanged,&toolreader,&SbiToolReader::readFrom);
    QObject::connect(&toolreader,&FileReader::DataReady,&w,&MainWindow::setbytes);
    QObject::connect(&RsReader,&FileReader::DataReady,&w,&MainWindow::setbytes);

   return a.exec();
}
