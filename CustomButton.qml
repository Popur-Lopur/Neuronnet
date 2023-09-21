import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.2

Button {
    id: myBtn
    width: 92.5
    height: 30
    background: Rectangle {
        radius: 5
        border.color: "black"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.9; color: myBtn.pressed ? "#434343" : "#000000" }
            GradientStop { position: 0.6; color: "#434343" }
        }
    }
    contentItem: Text {
        text: myBtn.text
        font: myBtn.font
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        color: myBtn.down ? "#7fff00" : "#fff5ee"
    }
}
