import QtQuick 2.0

Rectangle {
    id: fish
    signal onChangeDestination(int width, int height);
    Image {
        source: "fish.svg"
        MouseArea {
            acceptedButtons: Qt.RightButton
            anchors.fill: parent
            onClicked: fishManager.fishClicked(mouseX,mouseY)
        }

        Component.onCompleted: {
            fishManager.registerFish(fish, aquarium.width,aquarium.height);
        }

        /*transitions: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.InOutQuad }
        }*/
    }
}
