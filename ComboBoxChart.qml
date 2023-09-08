import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id:com
    height: 30
    width: 450

    signal vectorSelected(var data);

    function modelData() {

        combo.model = comboboxload.dataList
    }
    function modelTrainData() {

        combo.model = comboboxload.dataTrainList
    }




    ComboBox {
        id: combo


        font.wordSpacing: -0.1
        background: Rectangle {
            id: rectCombo
            anchors.fill: parent
            radius: 5
            gradient: Gradient {
                orientation: Gradient.Horizontal

                GradientStop { position: 0.9; color: "#4b6cb7" }
                GradientStop { position: 0.6; color: "#182848" }
            }




            border.color: "black"
        }

        anchors.fill: parent

        model: model2

        textRole: "id"
        onActivated: {

                    var vec =  model[index].vec
                    com.vectorSelected(vec);

        }
        contentItem: Label {
                text: combo.displayText
                font: combo.font
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                color: "white"
            }
    }
}
