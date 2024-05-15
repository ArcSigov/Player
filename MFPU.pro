QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/gui/about.cpp \
    src/gui/button.cpp \
    src/reader/cfgwriter.cpp \
    src/gui/display.cpp \
    src/reader/filereader.cpp \
    src/reader/fontreader.cpp \
    src/gui/label.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/parser/mfpudataparser.cpp \
    src/reader/sbireader.cpp \
    src/reader/sbitoolreader.cpp \
    src/gui/settings.cpp \
    src/gui/treemanager.cpp

HEADERS += \
    src/gui/about.h \
    src/gui/button.h \
    src/reader/cfgwriter.h \
    src/gui/display.h \
    src/reader/filereader.h \
    src/reader/fontreader.h \
    src/gui/label.h \
    src/gui/mainwindow.h \
    src/parser/mfpudataparser.h \
    src/reader/sbireader.h \
    src/reader/sbitoolreader.h \
    src/gui/settings.h \
    src/gui/treemanager.h
    src/pult.h
    src/utils.h

FORMS += \
    src/gui/about.ui \
    src/gui/mainwindow.ui \
    src/gui/settings.ui

resources.files = \
    images/pult.PNG \
    images/tu.png \
    images/tu_mini.png

LIBS += -LC:\Qt\Qt5.15.2\Tools\mingw730_64\x86_64-w64-mingw32\lib     -llibopengl32

RESOURCES = resources

RC_ICONS = images/tu.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target





