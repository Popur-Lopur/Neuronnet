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

    function showToolTip(x, y) {
        toolText.text = "X: " + x.toFixed(2) + ", Y: " + y.toFixed(2);
        mainToolTip.visible = true;
        mainToolTip.x = mouseX;
        mainToolTip.y = mouseY;
    }

    function hideToolTip() {
        mainToolTip.visible = false;
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
                axisX.max = 25000;
                axisY.min = 0;
                axisY.max = 160;
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



