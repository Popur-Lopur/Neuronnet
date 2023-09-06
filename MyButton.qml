import QtQuick 2.0

Rectangle {
    color: "lightblue"
    border.color: "blue"
    border.width: 2
    radius: 5
    Text {
        anchors.centerIn: parent
        //text: "My Button"
        color: "white"
        font.bold: true
    }
    MouseArea {
        anchors.fill: parent
        onClicked: console.log("Button clicked")
    }
}
