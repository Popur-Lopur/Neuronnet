import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.12
import NeuronNetworkManager 1.0

Item {
    id: pn3

    width: 185
    height: 70
    property int lenght: 40
    property int row: 28

    property string fieldGpText: ""
    property string fieldCgpText: ""
    property string fieldCbpText: ""
    property string fieldBpText: ""

    Rectangle {
        id: rectCol
        anchors.fill: parent
        radius: 5
        color: "transparent"

        RowLayout {
            id: rowText
            spacing: 5
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5



            Rectangle{
                id: rectGp
                width: lenght
                height: row
                border.color: "black"
                radius: 5
                gradient: Gradient {
                    orientation: Gradient.Vertical

                    GradientStop { position: 0.9; color: "#434343" }
                    GradientStop { position: 0.6; color: "#434343" }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Gp"
                    color: "white"
                }
            }

            Rectangle{
                id: rectCgp
                width: lenght
                height: row
                border.color: "black"
                radius: 5
                gradient: Gradient {
                    orientation: Gradient.Vertical

                    GradientStop { position: 0.9; color: "#434343" }
                    GradientStop { position: 0.6; color: "#434343" }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Cgp"
                    color: "white"
                }
            }

            Rectangle{
                id: rectCbp
                width: lenght
                height: row
                border.color: "black"
                radius: 5
                gradient: Gradient {
                    orientation: Gradient.Vertical

                    GradientStop { position: 0.9; color: "#434343" }
                    GradientStop { position: 0.6; color: "#434343" }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Cbp"
                    color: "white"
                }
            }

            Rectangle{
                id: rectBp
                width: lenght
                height: row
                border.color: "black"
                radius: 5
                gradient: Gradient {
                    orientation: Gradient.Vertical

                    GradientStop { position: 0.9; color: "#434343" }
                    GradientStop { position: 0.6; color: "#434343" }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Bp"
                    color: "white"
                }
            }
        }

        RowLayout {
            id: rowValues
            spacing: 5
            anchors.top: rowText.bottom
            anchors.left: parent.left
            anchors.margins: 5

            Rectangle{
                id: rectGpVal
                width: lenght
                height: row
                border.color: "black"
                radius: 5


                TextField {
                    id: fieldGp
                    anchors.fill: parent
                    color: "white"
                    onTextChanged: {
                        fieldGpText = text
                    }
                    background: Rectangle {
                        width: lenght
                        height: row
                        border.color: "black"
                        radius: 5
                        gradient: Gradient {
                            orientation: Gradient.Vertical
                            GradientStop { position: 0.9; color: "#434343" }
                            GradientStop { position: 0.6; color: "#434343" }
                        }
                    }
                }
            }



            Rectangle{
                id: rectCgpVal
                width: lenght
                height: row
                border.color: "black"
                radius: 5


                TextField {
                    id: fieldCgp
                    anchors.fill: parent
                    color: "white"
                    onTextChanged: {
                        fieldCgpText = text
                    }
                    background: Rectangle {
                        width: lenght
                        height: row
                        border.color: "black"
                        radius: 5
                        gradient: Gradient {
                            orientation: Gradient.Vertical
                            GradientStop { position: 0.9; color: "#434343" }
                            GradientStop { position: 0.6; color: "#434343" }
                        }
                    }
                }
            }

            Rectangle{
                id: rectCbpVal
                width: lenght
                height: row
                border.color: "black"
                radius: 5

                TextField {
                    id: fieldCbp
                    anchors.fill: parent
                    color: "white"

                    onTextChanged: {
                        fieldCbpText = text

                    }
                    background: Rectangle {
                        width: lenght
                        height: row
                        border.color: "black"
                        radius: 5
                        gradient: Gradient {
                            orientation: Gradient.Vertical

                            GradientStop { position: 0.9; color: "#434343" }
                            GradientStop { position: 0.6; color: "#434343" }

                        }
                    }
                }
            }

            Rectangle{
                id: rectBpVal
                width: lenght
                height: row
                border.color: "black"
                radius: 5

                TextField {
                    id: fieldBp
                    anchors.fill: parent
                    color: "white"
                    onTextChanged: {
                        fieldBpText = text
                    }
                    background: Rectangle {
                        width: lenght
                        height: row
                        border.color: "black"
                        radius: 5
                        gradient: Gradient {
                            orientation: Gradient.Vertical

                            GradientStop { position: 0.9; color: "#434343" }
                            GradientStop { position: 0.6; color: "#434343" }
                        }
                    }
                }
            }
        }
    }
}
