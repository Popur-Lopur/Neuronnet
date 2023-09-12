import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id: errorplot
    height: 280

    function plotData() {


        lineSeries.clear();
        for (var i = 0; i < neuron.ErrorValue.length ; i++) {
            var x = (i + 1) / neuron.ErrorValue.length * panel.fieldEpochText;

            lineSeries.append(x, neuron.ErrorValue[i]);
        }
    }

    ChartView {
        id: chart
        anchors.fill: parent
//        antialiasing: true


        ValueAxis {
            id: axisX

            min: 0

            max: panel.fieldEpochText
            tickCount: parseInt(max) + 1
            minorTickCount:neuron.ErrorValue.length
            minorGridVisible: false


        }

        ValueAxis {
            id: axisY

            min: 0
            max: 1.0
            tickCount: 11
            minorGridVisible: false

        }

        LineSeries {
            id: lineSeries

            name: "Network Errors"
            axisX: axisX
            axisY: axisY

        }
    }
}


