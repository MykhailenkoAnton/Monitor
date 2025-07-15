import QtQuick
import QtQuick.Controls
import "qml"

ApplicationWindow {
    readonly property alias pageStack: stackView

    id: app
    visible: true
    width: 1080
    height: 520
    title: qsTr("Monitor")
    //color: "#121212"

    StackView {
        id: stackView
        initialItem: ProcessScreen {}
        anchors.fill: parent
    }
}