import QtQuick

ListView {

    id: listMy
    anchors.fill: parent
    model: ProcessesModel

    delegate: Item  {
        height: 100
        width: 100

        Text {
            text: "Placeholder"
            anchors.fill: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("data change successful?");
            }
        }
    }
}