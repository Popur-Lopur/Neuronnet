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
    width: 1250
    height: 700
    title: qsTr("Qvazi")
    color: "#948E99"


//    Rectangle {
//        id:fon
//        color: "#0f2027"
//        //color: "#0f2027"
//        anchors.fill: parent
//        gradient: Gradient {

//            GradientStop { position: 0.9; color: "#0f2027" }
//            GradientStop { position: 0.6; color: "#203a43" }
//            GradientStop { position: 0.2; color: "#2c5364" }

//        }
//    }



    function updateColor() {
        win.color = Qt.rgba(Math.random(), Math.random(), Math.random());
    }

    Button {
        id: trainBtn
        text: "TRAIN"

        anchors.top: testBtn.bottom
        anchors.left: panel.right
        anchors.margins: 10





        onClicked: {

            comboboxload.loadDataTrain(panel.fieldDataText)
            comboChartFirst.modelTrainData()
            comboChartSecond.modelTrainData()

            neuron.runTrain()


        }
    }

    Button {
        id: testBtn        
        text: "TEST"
            anchors.top: btnStop.bottom
            anchors.left: panel.right
            anchors.margins: 10



        onClicked: {
            comboboxload.loadData(panel.fieldDataText)
            comboChartFirst.modelData()
            comboChartSecond.modelData()
            neuron.runTest()

        }
    }

    ResultText {
        id: resulttext
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 10

    }


    Charts {
        id: firstPlot
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        anchors.topMargin: 40

    }

    Charts {
        id: secondPlot
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
        anchors.bottomMargin: 10


    }

    ErrorChart {
        id: errorchart
        anchors.left: secondPlot.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        anchors.bottomMargin: 10


    }

    Panel {
        id: panel
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 10

    }



    ComboBoxChart {
        id: comboChartFirst
        anchors.right: firstPlot.right
        anchors.bottom: firstPlot.top
        anchors.bottomMargin: 1

    }

    ComboBoxChart {
        id: comboChartSecond
        anchors.right: secondPlot.right
        anchors.bottom: secondPlot.top
        anchors.bottomMargin: 1

    }

    Button {
        id: btnStop
        anchors.top: parent.top
        anchors.left: control.right        
        contentItem: Rectangle {
            radius: 5
            anchors.fill: parent
            gradient: Gradient {
                orientation: Gradient.Vertical

                GradientStop { position: 0.9; color: "#4b6cb7" }
                GradientStop { position: 0.6; color: "#182848" }
            }

            Text {
                        text: btnStopText.text
                        anchors.centerIn: parent
                    }
        }

        anchors.margins: 10

        Text {
            id: btnStopText
            text: "STOP"
            anchors.centerIn: parent
            color: "white"
        }
        onClicked: {
            updateColor();
            errorchart.plotData();



       }
    }

    Button {
        id: btnSave
        anchors.top: panel.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.margins: 10


        Text {
            id: btnSaveText
            text: "SAVE"
            anchors.centerIn: parent
            color: "black"
        }
        onClicked: {

            neuron.setEpoch(panel.fieldEpochText)
            neuron.setNumberHidden(panel.fieldHiddenText)
            neuron.setNumberOutput(panel.fieldOutputText)
            neuron.setLearningRate(panel.fieldLrText)
            neuron.setFilename(panel.fieldDataText)
            neuron.setFilenameValid(panel.fieldDataValidText)
            neuron.setWeights(panel.fieldWeightText)



        }
    }

    ProgressBar {
        id: control
        value: neuron.ValueProgressBar
        from: 0
        to: neuron.MaxValueProgressBar
        padding: 1
        anchors.top: btnSave.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20



        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 6
            color: "#e6e6e6"
            radius: 3
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
    Connections {
        target: comboChartSecond
        onVectorSelected: {
            secondPlot.vectorReceived(data);
        }
    }
    Connections {
        target: btnStop
        onErrorValueChanged: {
            errorchart.plotData();
        }
    }



}



