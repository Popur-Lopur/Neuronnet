import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id:com
    height: 30
    width: 405

    signal vectorSelected(var data);

    function modelData() {

        combo.model = comboboxload.dataList
    }
    function modelTrainData() {

        combo.model = comboboxload.dataTrainList
    }


    ComboBox {
        id: combo
        anchors.fill: parent
        textRole: "id"
        font.wordSpacing: -0.1
        background: Rectangle {
            id: rectCombo
            anchors.fill: parent
            radius: 5
            gradient: Gradient {
                orientation: Gradient.Horizontal

                GradientStop { position: 0.0; color: "#434343" }
                GradientStop { position: 1.0; color: "#434343" }
            }

        }
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
