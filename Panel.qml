import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.2
import NeuronNetworkManager 1.0


Item {
    id: p22

    width: 200
    height: 200
    property int lenght: 70
    property int row: 28
    property int lenghtVal: 110
    property string fieldWeightText: ""
    property string fieldOutputText: ""
    property string fieldHiddenText: ""
    property string fieldLrText: ""
    property string fieldEpochText: ""
    property string fieldDataText: ""




    Rectangle {
        id: rectCol
        anchors.fill: parent
        radius: 5
        color: "#ffefd5"
        border.color: "black"

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

                Text {
                    anchors.centerIn: parent
                    text: "Filename"
                }
            }

            Rectangle{
                id: rectEpoch
                width: lenght
                height: row
                border.color: "black"
                //radius: 5

                Text {
                    anchors.centerIn: parent
                    text: "Epochs"
                }
            }

            Rectangle{
                id: rectLr
                width: lenght
                height: row
                border.color: "black"
                //radius: 5

                Text {
                    anchors.centerIn: parent
                    text: "Lr"
                }
            }

            Rectangle{
                id: rectHidden
                width: lenght
                height: row
                border.color: "black"
                //radius: 5

                Text {
                    anchors.centerIn: parent
                    text: "Hidden"
                }
            }

            Rectangle{
                id: rectOutput
                width: lenght
                height: row
                border.color: "black"
                //radius: 5

                Text {
                    anchors.centerIn: parent
                    text: "Output"
                }
            }

            Rectangle{
                id: rectWeight
                width: lenght
                height: row
                border.color: "black"
                //radius: 5

                Text {
                    anchors.centerIn: parent
                    text: "Weights file"
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
                    id: fieldData
                    anchors.fill: parent
                    //text: "C:\\Work\\Qvazi\\test-xxx726.csv"
                    onTextChanged: {
                        fieldDataText = "C:\\Work\\QvaziWindow\\" + text + ".csv"
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
                    //text: "4"
                    onTextChanged: {
                        fieldEpochText = text
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
                    //text: "0.003"
                    onTextChanged: {
                        fieldLrText = text
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
                    //text: "400"
                    onTextChanged: {
                        fieldHiddenText = text
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
                    //text: "1"
                    onTextChanged: {
                        fieldOutputText = text
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
                    onTextChanged: {
                        fieldWeightText = "C:\\Work\\QvaziWindow\\" + text + ".txt"
                    }

                }
            }
        }
    }
}
