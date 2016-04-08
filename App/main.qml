import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.bbv.StreetLightSimulator 1.0

ApplicationWindow {
    title: qsTr("Street light simulator")
    objectName: "gui"
    //width: 1024
    //height: 768
    visible: true
    Component.onCompleted: updateStreetImage();

    /* menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"));
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }*/

    Rectangle {
        width: 1024
        height: 768

        Image {
            id: streetImage
            anchors.fill: parent
            source: "strasse_tag"
            fillMode: Image.PreserveAspectFit
        }
        Image {
            id: lightsource
            anchors.fill: parent
            source: ""
            fillMode: Image.PreserveAspectFit
            opacity: luminosityObject.luminosity
        }


    }

    /*MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }*/

    Timer {
        repeat: true
        running: true
        onTriggered: updateStreetImage();
    }

    DaySimulator {
        id: daySimulator
    }

    Item {
        id:brightnessObject
        property double brightness: cppBrightness.scaled
        onBrightnessChanged: {
            if(brightness > 0)
                streetImage.source = "strasse_tag"
            else
                streetImage.source = "strasse_nacht"
        }
    }
    Item {
        id:luminosityObject
        property double luminosity: cppLuminosity.scaled
        onLuminosityChanged: {
            if(luminosity > 0)
              lightsource.source = "light"
            else
                lightsource.source = ""
        }
    }

    function updateStreetImage() {
        var now = Math.floor(new Date().getTime() / 1000);
        //console.log("It is now "+now+" it is: "+now%daySimulator.dayDuration);
        if(daySimulator.getTimeOfDay(now) === DaySimulator.DAY)
            cppBrightness.scaled = 1;
        else
            cppBrightness.scaled = 0
    }

}
