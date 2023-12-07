import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.12


import NeuronNetworkManager 1.0


Window {
    id: win
    visible: true
    width: 1360
    height: 685
    title: qsTr("Qvazi")


    Rectangle {
           id:fon
           anchors.fill: parent
           gradient: Gradient {
               orientation: Gradient.Vertical
               GradientStop { position: 0.0; color: "#333333" }
               GradientStop { position: 1.0; color: "#000000" }

//               GradientStop { position: 0.9; color: "#0f2027" }
//               GradientStop { position: 0.6; color: "#203a43" }
//               GradientStop { position: 0.2; color: "#2c5364" }

           }
       }



    ResultText {
        id: resulttext        
        anchors.right: parent.right
        anchors.top: parent.top

        anchors.margins: 5

    }

    Image {
        source: "images/turtle.svg"
        width: 230
        height: 210
        anchors.bottom: parent.bottom
        anchors.right: firstPlot.left
        anchors.margins: 5



    }


    Charts {
        id: firstPlot
        anchors.right: parent.right
        anchors.top: comboChartFirst.bottom
        anchors.margins: 5


    }


//    ErrorChart {
//        id: errorchart
//        anchors.left: parent.left
//        anchors.top: parent.top
//        anchors.margins: 5


//    }

    ErrorValidChart {
        id: errorvalidchart

        anchors.left: parent.left
        anchors.top: errorchart.bottom
        anchors.margins: 5

    }

    Panel {
        id: panel
        anchors.top: parent.top
        anchors.right: resulttext.left


    }

    PanelBtnBar {
        id: panelBtnBar
        anchors.top: control.bottom
        anchors.right: resulttext.left
        anchors.margins: 5
    }

    ConfigPanel {
        id: configPanel
        anchors.top: parent.top
        anchors.right: panel.left
        anchors.rightMargin: 5
    }



    ComboBoxChart {
        id: comboChartFirst
        anchors.top: resulttext.bottom
        anchors.right: parent.right
        anchors.margins: 5
    }


    ProgressBar {
        id: control
        value: neuron.ValueProgressBar
        from: 0
        to: neuron.MaxValueProgressBar
        padding: 1
        anchors.top: panel.bottom
        anchors.right: resulttext.left
        anchors.margins: 5
        background: Rectangle {
            id: rectBar
            implicitWidth: 200
            implicitHeight: 6
            radius: 3
            color: "#fff5ee"

        }

        Text {
            id: progressText
            anchors.centerIn: parent
            color: "black"
            text: neuron.EpochProgressBar + "/" + neuron.MaxEpochProgressBar

        }

        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 20

            Rectangle {
                id: bar
                width: control.visualPosition * parent.width
                height: parent.height
                radius: 2
                color: "transparent"/*"#17a81a"*/
                LinearGradient {
                    anchors.fill: parent
                    start: Qt.point(0, 0)
                    end: Qt.point(parent.width, 0)
                    gradient: Gradient {

                        GradientStop { position: 0.0; color: "#a8e063" }
                        GradientStop { position: 0.9; color: "#56ab2f" }
                    }
                }
            }
        }
    }

    Connections {
        target: comboChartFirst
        onVectorSelected: {
            firstPlot.vectorReceived(data);
        }
    }
}



