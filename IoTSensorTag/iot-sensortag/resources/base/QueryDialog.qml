import QtQuick 2.6
import QtQuick.Controls 2.1
import Style 1.0

Rectangle {
    id: root

    opacity: 0.8

    property int borderWidth: 4

    signal dialogClosed(int mode, string address)

    //    visible: opacity > 0.2
    border {
        width: borderWidth
        color: "white"
    }

    Image {
        source: "images/bg_blue.jpg"
        anchors {
            fill: parent
            margins: borderWidth
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 48

        Button {
            id: simulationButton
            text: qsTr("Simulation Mode")
            width: 0.8 * root.width
            contentItem: Text {
                text: simulationButton.text
                font.pixelSize: Style.topToolbarLargeFontSize
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
            onClicked: {
                root.opacity = 0.2
                dialogClosed(0, "")
            }
        }

        Button {
            id: sensorButton
            property bool addressQuery: false
            text: !addressQuery ? qsTr("Sensor Mode") : qsTr(
                                      "Enter Tag Mac Address Below")
            width: 0.8 * root.width

            contentItem: Text {
                text: sensorButton.text
                font.pixelSize: !sensorButton.addressQuery ? Style.topToolbarLargeFontSize : Style.indicatorTitleSize
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
            onClicked: {
                if (addressQuery) {
                    root.opacity = 0.2
                    dialogClosed(1, textInput.text)
                }
                addressQuery = !addressQuery
                textInput.visible = true
            }
        }

        TextInput {
            id: textInput
            visible: false
            width: 0.8 * root.width
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: Style.topToolbarLargeFontSize
            text: "24:71:89:BC:44:82"
        }
    }

    Behavior on opacity {
        NumberAnimation {
        }
    }
}
