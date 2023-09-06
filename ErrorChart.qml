import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id: errorplot

    width: 560
    height: 300

     property var yValues: []

    function plotData() {
//        console.log("=============== 1 =================")
//        for (var k = 0; k < 10; k++){
//            console.log("-->" + neuron.ErrorValue[k])
//        }
//        console.log("=============== 1 =================")

        lineSeries.clear();
        //yValues = neuron.ErrorValue;
        for (var i = 0; i < neuron.ErrorValue.length ; i++) {
            var x = i + 1;
            lineSeries.append(x, neuron.ErrorValue[i]);
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
                //tickCount: axisX.max + 1
                //minorTickCount: 3

            }

            ValueAxis {
                id: axisY
                min: 0
                max: 1.0
                tickCount: 11



            }

            LineSeries {
                id: lineSeries
                name: "Network Errors"
                axisX: axisX
                axisY: axisY
//                Component.onCompleted: {
//                            var errorValues = neuron.ErrorValue;
//                            for (var i = 0; i < errorValues.length; ++i) {
//                                x = i + 1
//                                lineSeries.append(x, errorValues[i]);
//                            }
//                        }

            }
        }
    }
}
