import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id: errorvalidplot
    height: 335
    width: 700

    function plotValidData() {


        lineSeriesValid.clear();
        for (var i = 0; i < neuron.ErrorValueValid.length ; i++) {
            var x = (i + 1) / neuron.ErrorValueValid.length * panel.fieldEpochText;

            lineSeriesValid.append(x, neuron.ErrorValueValid[i]);
        }
    }

    Rectangle {

        id: rectValidPlot
        anchors.fill: parent
        radius: 5
        gradient: Gradient {
            orientation: Gradient.Vertical

            GradientStop { position: 1.0; color: "#000000" }
            GradientStop { position: 0.0; color: "#434343" }
        }


    }


    ChartView {
        id: chart
        anchors.fill: parent
        backgroundColor: "transparent"

        ValueAxis {
            id: axisYvalid

            max: 1.0
            tickCount: 11
            minorGridVisible: false
            color: "gray"
            labelsColor: "gray"
            gridLineColor: "gray"
            minorGridLineColor: "transparent"


        }

        ValueAxis {
            id: axisXvalid

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

        LineSeries {
            id:lineSeriesValid
            name:"<font color='#fff5ee'>Valid Errors</font>"

            axisX: axisXvalid
            axisY: axisYvalid
            color: "#ee82ee"

        }
    }
}

