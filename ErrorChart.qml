import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id: errorplot

    width: 560
    height: 300


    function plotData() {


        lineSeries.clear();
        for (var i = 0; i < neuron.ErrorValue.length ; i++) {
            var x = i + 1;
            lineSeries.append(x, neuron.ErrorValue[i]);
        }
    }

    function plotValidData() {


        lineSeriesValid.clear();
        for (var i = 0; i < neuron.ErrorValueValid.length ; i++) {
            var x = i + 1;
            lineSeries.append(x, neuron.ErrorValueValid[i]);
        }
    }





    Rectangle {
        id: rectPlot
        anchors.fill: parent
        //radius: 10
        border.color: "black"
        border.width: 1

        ChartView {
            id: chart
            anchors.fill: parent
            antialiasing: true





            ValueAxis {
                id: axisX
                min: 0
                max: panel.fieldEpochText * neuron.MaxValueProgressBar
                minorTickCount:neuron.ErrorValue.length


            }

            ValueAxis {
                id: axisY
                min: 0
                max: 1.0
                tickCount: 11



            }

            ValueAxis {
                id: axisYvalid
                max: 1.0
                tickCount: 11



            }

            ValueAxis {
                id: axisXvalid
                min: 0
                max: panel.fieldEpochText
                tickCount: panel.fieldEpochText
                minorTickCount: neuron.ErrorValueValid.length



            }

            LineSeries {
                id: lineSeries
                name: "Network Errors"
                axisX: axisX
                axisY: axisY


            }

            LineSeries {
                id: lineSeriesValid
                name: "Valid Errors"
                axisX: axisXvalid
                axisY: axisYvalid


            }
        }
    }
}
