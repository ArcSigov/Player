#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "fontreader.h"
#include "sbireader.h"
#include "sbitoolreader.h"
#include "mfpudataparser.h"
#include "cfgwriter.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    auto path = QDir::currentPath();
    QDir::setCurrent(path);
    MainWindow    w;
    MfpuDataParser parser;
    FontReader    reader(nullptr,ByteSeq::LittleEndian);
    SbiRSReader   RsReader;
    SbiToolReader toolreader;
    CfgReader     cfgreader;

    w.readfonts(reader.readFrom("font_mfpu.sre"));
    w.show();


   QObject::connect(&w,&MainWindow::FileChanged,&toolreader,&SbiToolReader::readFrom);
   QObject::connect(&toolreader,&FontReader::DataReady,&parser,&MfpuDataParser::parseData);
   QObject::connect(&parser,&MfpuDataParser::dataUpgraded,&w,&MainWindow::updateData);
   return a.exec();
}
