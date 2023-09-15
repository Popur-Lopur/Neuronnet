import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id: errorvalidplot
    height: 280

    function plotValidData() {


        lineSeriesValid.clear();
        for (var i = 0; i < neuron.ErrorValueValid.length ; i++) {
            var x = (i + 1) / neuron.ErrorValueValid.length * panel.fieldEpochText;

            lineSeriesValid.append(x, neuron.ErrorValueValid[i]);
        }
    }


    ChartView {
        id: chart
        anchors.fill: parent
//        antialiasing: true

        ValueAxis {
            id: axisYvalid

            max: 1.0
            tickCount: 11
            minorGridVisible: false

        }

        ValueAxis {
            id: axisXvalid

            min: 0

            max: panel.fieldEpochText
            tickCount: parseInt(max) + 1
            minorTickCount: 1600
            minorGridVisible: false

        }

        LineSeries {
            id:lineSeriesValid
            name: "Valid Errors"

            axisX: axisXvalid
            axisY: axisYvalid

        }
    }
}

