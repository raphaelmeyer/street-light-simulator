TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= qt
CONFIG += coverage
QT += quick
QT += widgets
QT += testlib qml
QT += dbus
CONFIG += c++14

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage -O0 -lgcov --coverage

INCLUDEPATH += ../test/ \
    ../App/

SOURCES += \
 ../App/daysimulator.cpp \
../App/stateexchanger.cpp \
    ../App/dbusobject.cpp  \
    ../App/eventsimulator.cpp  \
    ../App/rainsimulator.cpp  \
    daysimulator_test.cpp \
    stateexchanger_test.cpp \
    eventsimulator_test.cpp \
    Main_TestAll.cpp \
    rainsimulator_test.cpp



HEADERS += \
../App/daysimulator.h \
../App/stateexchanger.h \
../App/eventsimulator.h \
../App/rainsimulator.h \
dbusobject.h


#include(deployment.pri)
#qtcAddDeployment()


LIBS += -lgtest -pthread -lgtest_main -lgcov --coverage
