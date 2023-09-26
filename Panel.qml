import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.12
import NeuronNetworkManager 1.0


Item {
    id: pn1

    width: 200
    height: 230
    property int lenght: 70
    property int row: 28
    property int lenghtVal: 110
    property string fieldWeightText: ""
    property string fieldOutputText: ""
    property string fieldHiddenText: ""
    property string fieldLrText: ""
    property string fieldEpochText: ""
    property string fieldDataText: ""
    property string fieldDataValidText: ""




    Rectangle {
        id: rectCol
        anchors.fill: parent
        radius: 5
        color: "transparent"


        ColumnLayout {
            id: colText
            spacing: 4
            anchors.left: parent.left
            anchors.margins: 5
            anchors.verticalCenter: parent.verticalCenter

            Rectangle{
                id: rectData
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
                    text: "Filename"
                    color: "white"
                }
            }



            Rectangle{
                id: rectDataValid
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
                    text: "File Valid"
                    color: "white"
                }
            }

            Rectangle{
                id: rectEpoch
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
                    text: "Epochs"
                    color: "white"
                }
            }

            Rectangle{
                id: rectLr
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
                    text: "Lr"                    
                    color: "white"
                }
            }

            Rectangle{
                id: rectHidden
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
                    text: "Hidden"
                    color: "white"
                }
            }

            Rectangle{
                id: rectOutput
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
                    text: "Output"
                    color: "white"
                }
            }

            Rectangle{
                id: rectWeight
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
                    text: "Weights file"
                    color: "white"
                }
            }
        }

        ColumnLayout {
            id: colValues
            spacing: 4
            anchors.left: colText.right
            anchors.margins: 5
            anchors.verticalCenter: parent.verticalCenter

            Rectangle{
                id: rectDataVal
                width: lenghtVal
                height: row
                border.color: "black"
                radius: 5


                TextField {
                    id: fieldDataTrain
                    anchors.fill: parent
                    color: "white"
                    onTextChanged: {
                        fieldDataText = "C:\\Work\\QvaziWindow\\" + text + ".csv"
                    }
                    background: Rectangle {
                        width: lenghtVal
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
                id: rectDataValidVal
                width: lenghtVal
                height: row
                border.color: "black"
                radius: 5


                TextField {
                    id: fieldDataValid
                    anchors.fill: parent
                    color: "white"
                    onTextChanged: {
                        fieldDataValidText = "C:\\Work\\QvaziWindow\\" + text + ".csv"
                    }
                    background: Rectangle {
                        width: lenghtVal
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
                id: rectEpochVal
                width: lenghtVal
                height: row
                border.color: "black"
                radius: 5

                TextField {
                    id: fieldEpoch
                    anchors.fill: parent
                    color: "white"

                    onTextChanged: {
                        fieldEpochText = text

                    }
                    background: Rectangle {
                        width: lenghtVal
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
                id: rectLrVal
                width: lenghtVal
                height: row
                border.color: "black"
                radius: 5

                TextField {
                    id: fieldLr
                    anchors.fill: parent
                    color: "white"
                    //text: "0.003"
                    onTextChanged: {
                        fieldLrText = text
                    }
                    background: Rectangle {
                        width: lenghtVal
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
                id: rectHiddenVal
                width: lenghtVal
                height: row
                border.color: "black"
                radius: 5

                TextField {
                    id: fieldHidden
                    anchors.fill: parent
                    color: "white"
                    //text: "400"
                    onTextChanged: {
                        fieldHiddenText = text
                    }
                    background: Rectangle {
                        width: lenghtVal
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
                id: rectOutputVal
                width: lenghtVal
                height: row
                border.color: "black"
                radius: 5

                TextField {
                    id: fieldOutput
                    anchors.fill: parent
                    color: "white"
                    onTextChanged: {
                        fieldOutputText = text
                    }
                    background: Rectangle {
                        width: lenghtVal
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
                id: rectWeightVal
                width: lenghtVal
                height: row
                border.color: "black"
                radius: 5

                TextField {
                    id: fieldWeight
                    anchors.fill: parent
                    color: "white"
                    onTextChanged: {
                        fieldWeightText = "C:\\Work\\QvaziWindow\\" + text + ".json"
                    }
                    background: Rectangle {
                        width: lenghtVal
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
