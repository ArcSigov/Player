QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
MOC_DIR = .moc
OBJECTS_DIR = .obj
TARGET = pengl32
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    display.cpp \
    filereader.cpp \
    filter.cpp \
    fontreader.cpp \
    label.cpp \
    main.cpp \
    mainwindow.cpp \
    sbireader.cpp \
    sbitoolreader.cpp

HEADERS += \
    button.h \
    display.h \
    filereader.h \
    filter.h \
    fontreader.h \
    label.h \
    mainwindow.h \
    sbireader.h \
    sbitoolreader.h \
    utils.h

FORMS += \
    filter.ui \
    mainwindow.ui

resources.files = \
    pult.PNG

LIBS += -LC:\Qt\Qt5.15.2\Tools\mingw730_64\x86_64-w64-mingw32\lib     -opengl32

RESOURCES = resources

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target





