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
    height: 760
    title: qsTr("Qvazi")
    color: "#948E99"

    ResultText {
        id: resulttext        
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: errorvalidchart.top
        anchors.margins: 5

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
        anchors.left: firstPlot.right
        anchors.top: parent.top
        anchors.margins: 10
        anchors.topMargin: 40


    }

    ErrorChart {
        id: errorchart
        width: parent.width/2
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 5
        //anchors.bottomMargin: 5


    }

    ErrorValidChart {
        id: errorvalidchart
        width: parent.width/2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        //anchors.bottomMargin: 5


    }

    Panel {
        id: panel
        anchors.top: parent.top
        anchors.right: resulttext.left
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
        anchors.top: panel.bottom
        anchors.right: resulttext.left
        anchors.margins: 10

        Text {
            id: btnStopText
            text: "PUSH 1"
            anchors.centerIn: parent
            color: "black"
        }
        onClicked: {            
            errorchart.plotData();
       }
    }

    Button {
        id: btnPush
        anchors.top: control.bottom
        anchors.right: resulttext.left
        anchors.margins: 10

        Text {
            id: btnPushText
            text: "PUSH 2"
            anchors.centerIn: parent
            color: "black"
        }
        onClicked: {

            errorvalidchart.plotValidData();

       }
    }

    Button {
        id: btnSave
        anchors.top: panel.bottom
        anchors.right: btnStop.left
        anchors.margins: 10


        Text {
            id: btnSaveText
            text: "SAVE"
            anchors.centerIn: parent
            color: "black"
        }
        onClicked: {


            neuron.setWeights(panel.fieldWeightText)
            neuron.setEpoch(panel.fieldEpochText)
            neuron.setNumberHidden(panel.fieldHiddenText)
            neuron.setNumberOutput(panel.fieldOutputText)
            neuron.setLearningRate(panel.fieldLrText)
            neuron.setFilename(panel.fieldDataText)
            neuron.setFilenameValid(panel.fieldDataValidText)

        }
    }

    Button {
        id: trainBtn
        text: "TRAIN"

        anchors.top: btnSave.bottom
        anchors.right: testBtn.left
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
            anchors.right: resulttext.left
            anchors.margins: 10



        onClicked: {

            neuron.setFilename(panel.fieldDataText)
            neuron.setWeights(panel.fieldWeightText)
            comboboxload.loadData(panel.fieldDataText)
            comboChartFirst.modelData()
            comboChartSecond.modelData()
            neuron.runTest()

        }
    }

    ProgressBar {
        id: control
        value: neuron.ValueProgressBar
        from: 0
        to: neuron.MaxValueProgressBar
        padding: 1
        anchors.top: trainBtn.bottom
        anchors.right: testBtn.right
        anchors.topMargin: 5



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
}



