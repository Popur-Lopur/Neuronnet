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
            var x = (i + 1)  / neuron.ErrorValueValid.length * panel.fieldEpochText;

            lineSeriesValid.append(x, neuron.ErrorValueValid[i]);
        }
    }

    function showToolTip(x, y) {

        var currentBigDivision = Math.floor(x);
        var minorDivisionPerBigDivision = neuron.ErrorValueValid.length / panel.fieldEpochText;
        var minorDivisionNumber = Math.round((x  - currentBigDivision) * minorDivisionPerBigDivision);
        var minorNumber = Math.ceil(parseInt(minorDivisionNumber) / panel.fieldOutputText)
        var minorEpoch = parseInt(currentBigDivision) + 1

        toolText.text = "Num: " + minorNumber + " in Epoch: " + minorEpoch  + " Error: " + y.toFixed(4);


        mainToolTip.visible = true;
        mainToolTip.x = mouseX;
        mainToolTip.y = mouseY;
    }

    function hideToolTip() {
        mainToolTip.visible = false;
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
            id: axisY

            max: 1.0
            tickCount: 11
            minorGridVisible: false
            color: "gray"
            labelsColor: "gray"
            gridLineColor: "gray"
            minorGridLineColor: "transparent"


        }

        ValueAxis {
            id: axisX

            min: 0

            max: panel.fieldEpochText
            tickCount: parseInt(max) + 1
            minorTickCount: neuron.ErrorValueValid.length
            minorGridVisible: false
            color: "gray"
            labelsColor: "gray"
            gridLineColor: "gray"
            minorGridLineColor: "transparent"

        }

        LineSeries {
            id:lineSeriesValid
            name:"<font color='#fff5ee'>Valid Errors</font>"

            axisX: axisX
            axisY: axisY
            color: "#ee82ee"

            onHovered: {
                if (point !== undefined) {
                    var chartX = point.x;
                    var chartY = point.y;
                    showToolTip(chartX, chartY);
                } else {
                    hideToolTip();
                }
            }

            onPressed: {
                if (point !== undefined) {
                    hideToolTip();
                }
            }
        }
    }

    ToolTip {
        id: mainToolTip
        visible: false
        delay: 0
        timeout: 3000
        background: Rectangle {
            opacity: 0.8
            radius: 5
            color: "white"
        }
        contentItem: Text {
            id: toolText
            color: "black"
            font.pointSize: 12
        }
    }


    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: false
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        property real lastX: 0
        property real lastY: 0

        function windowToChartCoordinates(x, y) {
            var chartX = axisX.min + (x / chart.width) * (axisX.max - axisX.min);
            var chartY = axisY.max - (y / chart.height) * (axisY.max - axisY.min);
            return {chartX: chartX, chartY: chartY};
        }

        onPositionChanged: {
            var coords = windowToChartCoordinates(mouseX, mouseY);
            coordinatesDisplay.text = "X: " + coords.chartX.toFixed(2) + ", Y: " + coords.chartY.toFixed(2);
        }



        onClicked: {
            if (mouse.button === Qt.RightButton) {
                chart.zoomReset();
                axisX.min = 0;
                axisX.max = panel.fieldEpochText;
                axisY.min = 0;
                axisY.max = 1.0;
                mouse.accepted = true;
                return;
            }
            lastX = mouseX;
            lastY = mouseY;
        }

        onWheel: {
            var delta = wheel.angleDelta.y > 0 ? 1.1 : 1 / 1.1
            chart.zoom(delta);

        }

        onMouseXChanged: {
            if (pressed) {
                var dx = (lastX - mouseX) * (axisX.max - axisX.min) / chart.width;
                axisX.min += dx;
                axisX.max += dx;

                lastX = mouseX;
            }
        }

        onMouseYChanged: {
            if (pressed) {
                var dy = (lastY - mouseY) * (axisY.max - axisY.min) / chart.height;
                axisY.min += dy;
                axisY.max += dy;

                lastY = mouseY;
            }
        }
    }
}



