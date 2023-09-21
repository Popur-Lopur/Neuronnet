import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Rectangle {
    id: rectResult
    width: 200
    height: 335
    radius: 5
    gradient: Gradient {

        GradientStop { position: 0.9; color: "#fff5ee" }
        GradientStop { position: 0.6; color: "#fff5ee" }


    }

    ScrollView {
        id: scroll
        anchors.right: rectResult.right
        anchors.top: rectResult.top
        anchors.bottom: rectResult.bottom
        anchors.left: rectResult.left
        clip: true



        TextField {
            id: textField
            selectByMouse: true
            selectionColor: "#e6e6fa"
            wrapMode: Text.WordWrap
            font.pixelSize: 15
            implicitWidth: 110
            background: Rectangle {
                visible: false
            }
        }
    }



    Connections {
        target: neuron  // Связываем сигнал из C++ сигналом в QML
        onUpdateTextField: {
            textField.text += data
        }

    }
}

