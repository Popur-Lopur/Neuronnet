import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3


Item {
    id: plots

    width: 405
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

    Rectangle {

        id: rectChartPlot
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
            // Установка цвета фона в прозрачный цвет
            backgroundColor: "transparent"


            ValueAxis {
                id: axisX
                min: 0
                max: 25000
                tickCount: 6
                color: "gray"
                labelsColor: "gray"
                gridLineColor: "gray"


            }

            ValueAxis {
                id: axisY
                min: 0
                max: 160
                tickCount: 9
                color: "gray"
                labelsColor: "gray"
                gridLineColor: "gray"



            }

            LineSeries {
                id: lineSeries
                name: "<font color='#fff5ee'>Wideband</font>"
                axisX: axisX
                axisY: axisY
                color: "#00FFFF"

            }
        }
}



