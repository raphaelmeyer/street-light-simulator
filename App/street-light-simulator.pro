######################################################################
# Automatically generated by qmake (3.0) Do. M�r. 24 14:00:31 2016
######################################################################

TEMPLATE = app
TARGET = street-light-simulator
INCLUDEPATH += .
#QT += gui
QT += widgets
QT += qml
QT += quick
CONFIG += staticlib
CONFIG += release qt debug
CONFIG += c++14
CONFIG += coverage
LIBS += -lgcov --coverage

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage -O0 -lgcov --coverage

# Input
SOURCES += main.cpp \ 
    daysimulator.cpp \
    timeprovider.cpp
RESOURCES += qml.qrc \
    ressources.qrc


HEADERS += \
    daysimulator.h \
    timeprovider.h
