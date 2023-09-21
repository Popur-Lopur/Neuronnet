import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id: errorplot
    height: 335
    width: 700

    function plotData() {


        lineSeries.clear();
        for (var i = 0; i < neuron.ErrorValue.length ; i++) {
            var x = (i + 1) / neuron.ErrorValue.length * panel.fieldEpochText;

            lineSeries.append(x, neuron.ErrorValue[i]);
        }
    }

    Rectangle {

        id: rectErrorPlot
        anchors.fill: parent
        radius: 5
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 1.0; color: "#434343" }
        }


    }

    ChartView {
        id: chart
        anchors.fill: parent
        backgroundColor: "transparent"


        ValueAxis {
            id: axisX

            min: 0

            max: panel.fieldEpochText
            tickCount: parseInt(max) + 1
            minorTickCount: 1600
            minorGridVisible: false
            color: "gray"
            labelsColor: "gray"
            gridLineColor: "gray"
            minorGridLineColor: "transparent"




        }

        ValueAxis {
            id: axisY

            min: 0
            max: 1.0
            tickCount: 11
            minorGridVisible: false
            color: "gray"
            labelsColor: "gray"
            gridLineColor: "gray"
            minorGridLineColor: "transparent"




        }

        LineSeries {
            id: lineSeries
            name: "<font color='#fff5ee'>Network Errors</font>"
            axisX: axisX
            axisY: axisY
            color: "#ffff00"

        }
    }
}


