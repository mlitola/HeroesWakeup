import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.8

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("HeroesWakeUp")
    color: "#000000"
    visibility: Window.FullScreen

    // source: "file://home/mihko/Projects/Qt/heroesWakeUp/images/background.png"

    MouseArea {
        width: 1024
        height: 768
        id: mouseArea1
        anchors.rightMargin: 25
        anchors.fill: parent
        hoverEnabled: true
        onClicked: Qt.quit()
    }

    BorderImage {
        id: borderImage
        x: 0
        y: 0
        width: 1024
        height: 720
        border.top: 0
        source: "file://home/mihko/Projects/Qt/heroesWakeUp/images/background.png"

        Text {
            id: element
            x: 455
            y: 413
            width: 556
            height: 193
            color: "#7bc6ed"
            text: qsTr("00:00")
            font.bold: true
            font.family: "Arial"
            font.pixelSize: 216
        }
    }

    Audio {
        id: playMusic
        volume: 0.6
        source: "file://home/mihko/Projects/Qt/heroesWakeUp/sound/test.wav"
        autoLoad: true
        // autoPlay: true
    }
}
