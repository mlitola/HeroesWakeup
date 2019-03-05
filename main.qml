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

    MouseArea {
        width: 1024
        height: 768
        id: mouseArea1
        anchors.rightMargin: 25
        anchors.fill: parent
        hoverEnabled: true
        onClicked: Qt.quit()
    }
}
