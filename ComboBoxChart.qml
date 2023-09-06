import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3

Item {
    id:com
    height: 30
    width: 450

    signal vectorSelected(var data);


    ComboBox {
        id: combo
        font.wordSpacing: -0.1
        background: Rectangle {
            id: rectCombo
            anchors.fill: parent
            //radius: 5
            color: "#ffefd5"
            border.color: "black"
        }

        anchors.fill: parent

        model: comboboxload.dataList
        textRole: "id"
        onActivated: {

                    var vec =  model[index].vec
                    com.vectorSelected(vec);

        }
    }
}
