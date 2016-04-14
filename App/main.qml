import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.bbv.StreetLightSimulator 1.0

ApplicationWindow {
    title: qsTr("Street light simulator")
    id: gui
    objectName: "gui"
    visible: true
    width: 1024
    height: 768
    property int dayLength: 60
    property double scalingFactor: (1.0*streetImage.paintedWidth)/1024
    onScalingFactorChanged: console.log("New scaling factor "+scalingFactor)
    Rectangle {
        objectName: "world"
        id: world
        anchors.fill: parent

        Image {
            id: streetImage
            anchors.fill: parent
            source: "strasse_tag"
            fillMode: Image.PreserveAspectFit
            Connections {
                target: cppDay
                onDaytimeChanged: {
                    if(cppDay.daytime === DaySimulator.DAY) {
                        streetImage.source = "strasse_tag"
                        cppBrightness.scaled = 1
                    }
                    else {
                        streetImage.source = "strasse_nacht"
                        cppBrightness.scaled = 0
                    }
                }
            }
        }
        Image{
            id: sign
            source: cppWarning.phrase === "" ? "sign_inactive" : "sign_active"
            width: 72*scalingFactor
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: streetImage.verticalCenter
            anchors.horizontalCenter: streetImage.horizontalCenter
            anchors.horizontalCenterOffset: 80*scalingFactor
            Label {
                anchors.fill: parent
                anchors.topMargin: 20
                text: cppWarning.phrase
                color: "yellow"
                maximumLineCount: 6
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Image {
            id: lightsource
            anchors.fill: parent
            source: "light"
            opacity: cppLuminosity.scaled
            fillMode: Image.PreserveAspectFit
        }
        Image {
            id: sun
            source: "sun"
            objectName: "sun"
            fillMode: Image.PreserveAspectFit
            width: 60
            x: 0
            y: 400+cppDay.nightStart%60
            Behavior on x {
                NumberAnimation {
                    duration: 1000
                }
            }

        }
        Image {
            id: moon
            source: "moon"
            objectName: "moon"
            fillMode: Image.PreserveAspectFit
            width: 60
            x: 0
            y: 400+cppDay.nightStart%60
            visible: {
                if((x<0) || (x>parent.width))
                    return false;
                else
                    return true;
            }

            //Behavior on x {
            NumberAnimation on x {
                duration: 30000//(dayLength-(cppDay.nightStart%dayLength))*1000
                from: 0
                to: world.width
                loops: Animation.Infinite
            }
            //}

        }

        Image {
            id: rain
            anchors.fill: parent
            source: "rain"
            visible: false
            fillMode: Image.PreserveAspectFit
            Connections {
                target: cppRain
                onRainChanged: {
                    rain.visible = cppRain.rain
                    cppMoisture = cppRain.rain == true ? 1.0 : 0 ;
                }
            }
        }

        /*Image {
            id: auto
            source: "auto"
            x: (autoLocation.value)*1000
            y: 420 + (1-autoLocation.value)*100
            fillMode: Image.PreserveAspectFit
            width: parent.width/15 + (1-autoLocation.value)*400
            rotation: -25+(1-autoLocation.value)*25
        }*/
        function calculatePosition() {
            var now = Math.floor(new Date().getTime() / 1000)
            var sunX = gui.width/(cppDay.nightStart%dayLength)*(now%dayLength)
            var moonX = gui.width/(dayLength-(cppDay.nightStart%dayLength))*((now-cppDay.nightStart)%dayLength)
            console.log("sunX is now"+sunX+" moonX is now "+moonX)
            sun.x = sunX
            //moon.x = moonX
            console.log("Cal:"+(dayLength-(cppDay.nightStart%dayLength))*1000+"world width: "+world.width)

        }

    }

    /*Slider {
        id: autoLocation
        orientation: Qt.Horizontal
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        anchors.bottom: parent.bottom

        onValueChanged: {
            //console.log("Value is now"+value+"auto size:"+auto.width)
        }
    }*/



}
