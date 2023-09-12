import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3


Item {
    id: plots

    width: 450
    height: 300


    property var yValues: []
    property int xStep: 16

    signal vectorReceived(var data);

    function plotData() {
        lineSeries.clear();
        for (var i = 0; i < yValues.length; i++) {
            var x = i * xStep;
            lineSeries.append(x, yValues[i]);
        }
    }

    onVectorReceived: {
        yValues = data;
        plotData();
    }


        ChartView {
            id: chart
            anchors.fill: parent
            //antialiasing: true

            ValueAxis {
                id: axisX
                min: 0
                max: 25000
                tickCount: 6


            }

            ValueAxis {
                id: axisY
                min: 0
                max: 160               
                tickCount: 9


            }

            LineSeries {
                id: lineSeries
                name: "Wideband"
                axisX: axisX
                axisY: axisY

            }
        }
    }



