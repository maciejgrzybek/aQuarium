import QtQuick 2.0

Item
{
    id: button
    property string text
    property bool purpleButton: false

    signal clicked

    BorderImage {
        id: buttonImage
        source: "../images/" + (purpleButton ? "button_random.png" : "button_create.png")
        width: button.width; height: button.height
    }
    BorderImage {
        id: pressed
        opacity: 0
        source: buttonImage.source
        width: button.width; height: button.height
    }

    Text {
        color: "white"
        anchors.centerIn: buttonImage; font.bold: true; font.pixelSize: 15
        text: button.text; style: Text.Raised; styleColor: "black"
    }

    MouseArea {
        id: mouseRegion
        anchors.fill: buttonImage
        onClicked: { button.clicked(); }
    }

    states: [
        State {
            name: "Pressed"
            when: mouseRegion.pressed == true
            PropertyChanges { target: pressed; opacity: 1 }
        }
    ]
}
