cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME Player)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED Widgets Gui Core OpenGL)
find_package(OpenGL REQUIRED)

set                        (SEARCH_DIRS
                            src
                            src/gui
                            src/parser
                            src/reader
                            )

set (SOURCES  src/main.cpp
              src/gui/about.cpp
              src/gui/about.ui
              src/gui/button.cpp
              src/reader/cfgwriter.cpp
              src/gui/display.cpp
              src/reader/filereader.cpp
              src/reader/fontreader.cpp
              src/gui/label.cpp
              src/gui/mainwindow.cpp
              src/gui/mainwindow.ui
              src/parser/mfpudataparser.cpp
              src/reader/sbireader.cpp
              src/reader/sbitoolreader.cpp
              src/gui/settings.cpp
              src/gui/treemanager.cpp


              src/gui/about.h
              src/gui/button.h
              src/reader/cfgwriter.h
              src/gui/display.h
              src/reader/filereader.h
              src/reader/fontreader.h
              src/gui/label.h
              src/gui/mainwindow.h
              src/parser/mfpudataparser.h
              src/reader/sbireader.h
              src/reader/sbitoolreader.h
              src/gui/settings.h
              src/gui/treemanager.h
              src/pult.h
              src/utils.h)

qt5_add_resources(SOURCES resources.qrc)
add_executable(${PROJECT_NAME} ${SOURCES})
qt5_use_modules(${PROJECT_NAME} OpenGL)

target_link_libraries(${PROJECT_NAME}     Qt5::Widgets
                                          Qt5::Gui
                                          Qt5::Core
                                          ${OPENGL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SEARCH_DIRS})
