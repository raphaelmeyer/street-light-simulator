TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

RESOURCES += qml.qrc \
    ressources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    assets/images/auto.png \
    assets/images/strasse_nacht.tif \
    assets/images/strasse_tag_licht.tif \
    assets/images/strasse_tag.tif \
    assets/images/strasse_nacht_licht.tif
