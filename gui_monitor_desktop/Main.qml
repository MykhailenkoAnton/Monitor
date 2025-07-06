import QtQuick
import QtQuick.Controls

ApplicationWindow {
    readonly property alias pageStack: stackView

    id: app
    visible: true
    width: 1080
    height: 520
    title: qsTr("Monitor")

    StackView {
        id: stackView
        anchors.fill: parent
    }
}