import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.bbv.StreetLightSimulator 1.0

ApplicationWindow {
    title: qsTr("Street light simulator")
    //width: 1024
    //height: 768
    property bool streetLight: false;
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

    function updateStreetImage() {
        var now = Math.floor(new Date().getTime() / 1000);
        console.log("It is now "+now+" it is: "+now%daySimulator.dayDuration);
        if(daySimulator.getTimeOfDay(now) === DaySimulator.DAY) {
            if(streetLight)
                streetImage.source = "strasse_tag_licht"
            else
                streetImage.source = "strasse_tag"
        }
        else {
            if(streetLight)
                streetImage.source = "strasse_nacht_licht"
            else
                streetImage.source = "strasse_nacht"
        }

    }

}
