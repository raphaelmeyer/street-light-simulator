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
    property int defaultWidth: 1024
    width: defaultWidth
    height: 768
    property int dayLength: 60
    property double scalingFactor: (1.0*streetImage.paintedWidth)/defaultWidth
    //onScalingFactorChanged: console.log("New scaling factor "+scalingFactor)
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
                    }
                    else {
                        streetImage.source = "strasse_nacht"
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
            anchors.horizontalCenter: streetImage.horizontalCenter
            anchors.verticalCenter: streetImage.verticalCenter
            anchors.verticalCenterOffset: -300*scalingFactor
            fillMode: Image.PreserveAspectFit
            width: 60 * scalingFactor
            Behavior on anchors.horizontalCenterOffset {
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
            width: 60*scalingFactor
            visible: false
            anchors.verticalCenter: streetImage.verticalCenter
            anchors.verticalCenterOffset: -300*scalingFactor
            anchors.horizontalCenter: streetImage.horizontalCenter
            Behavior on anchors.horizontalCenterOffset {
                NumberAnimation {
                    duration: 1000
                }
            }
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

        function calculateCelestialPositions() {
            var now = Math.floor(new Date().getTime() / 1000)
            var maxOffset = scalingFactor*defaultWidth/2
            var sunX = scalingFactor*defaultWidth*(((now%dayLength)/(cppDay.nightStart%dayLength))-1/2)
            var moonX = defaultWidth*scalingFactor*(((now%dayLength-cppDay.nightStart%60)/(60-(cppDay.nightStart%dayLength)-1))-1/2)

            if( Math.abs(sunX) > maxOffset) {
                sunX = -(sun.paintedWidth/2+maxOffset)
                sun.visible = false
            }
            else {
                sun.visible = true
                cppBrightness.scaled = 1-Math.abs(sunX/maxOffset)
            }

            if(Math.abs(moonX) > maxOffset) {
                moonX = -(moon.paintedWidth/2+maxOffset)
                moon.visible = false
            }
            else {
                moon.visible = true
                cppBrightness.scaled = 0.1*(1-Math.abs(moonX/maxOffset))
            }
            //console.log("sunX is now "+sunX+" moonX is now "+moonX)
            //console.log("Brightness is "+cppBrightness.scaled)
            sun.anchors.horizontalCenterOffset = sunX
            moon.anchors.horizontalCenterOffset = moonX
        }

    }
}
