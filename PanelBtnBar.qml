import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.2

import NeuronNetworkManager 1.0

Item {
    id:pn2
    width: 200
    height: 75

    Rectangle {
        id: rectCol
        anchors.fill: parent
        color: "transparent"
        radius: 5


        CustomButton {
            id:btn1
            text: "TEST"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5
            onClicked: {

                neuron.setFilename(panel.fieldDataText)
                neuron.setWeights(panel.fieldWeightText)
                comboboxload.loadData(panel.fieldDataText)
                comboChartFirst.modelData()                
                neuron.runTest()

            }
        }

        CustomButton {
            id:btn2
            text: "TRAIN"
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 5
            onClicked: {

                neuron.setWeights(panel.fieldWeightText)
                neuron.setEpoch(panel.fieldEpochText)
                neuron.setNumberHidden(panel.fieldHiddenText)
                neuron.setNumberOutput(panel.fieldOutputText)
                neuron.setLearningRate(panel.fieldLrText)
                neuron.setFilename(panel.fieldDataText)
                neuron.setFilenameValid(panel.fieldDataValidText)

                comboboxload.loadDataTrain(panel.fieldDataText)
                comboChartFirst.modelTrainData()                

                neuron.runTrain()

            }
        }

        CustomButton {
            id:btn3
            text: "PUSH 1"
            anchors.top: btn1.bottom
            anchors.left: parent.left
            anchors.margins: 5
            onClicked: {
                errorchart.plotErrorData();
            }
        }

        CustomButton {
            id:btn4
            text: "PUSH 2"
            anchors.top: btn2.bottom
            anchors.right: parent.right
            anchors.margins: 5
            onClicked: {
                errorvalidchart.plotValidData();
            }
        }
    }
}

