QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    cfgwriter.cpp \
    display.cpp \
    filereader.cpp \
    fontreader.cpp \
    label.cpp \
    main.cpp \
    mainwindow.cpp \
    mfpudataparser.cpp \
    sbireader.cpp \
    sbitoolreader.cpp \
    treemanager.cpp

HEADERS += \
    button.h \
    cfgwriter.h \
    display.h \
    filereader.h \
    fontreader.h \
    label.h \
    mainwindow.h \
    mfpudataparser.h \
    sbireader.h \
    sbitoolreader.h \
    treemanager.h \
    utils.h

FORMS += \
    mainwindow.ui

resources.files = \
    pult.PNG

LIBS += -LC:\Qt\Qt5.15.2\Tools\mingw730_64\x86_64-w64-mingw32\lib     -llibopengl32

RESOURCES = resources

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target





