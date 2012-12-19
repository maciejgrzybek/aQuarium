import QtQuick 2.0

Item {
    id: fish
    width: 150
    height: 100
    property int identifier: 0
    Image {
        source: "fish.svg"
        fillMode: Image.PreserveAspectFit
        width: fish.width
        height: fish.height
        scale: 1
        MouseArea {
            acceptedButtons: Qt.RightButton
            anchors.centerIn: parent
            onClicked: fishManager.fishClicked(mouseX,mouseY)
        }

        Component.onCompleted: {
            identifier = fishManager.registerFish(aquarium.width*scale-fish.width,aquarium.height*scale-fish.height);
            console.log("Fish completed. Id = " + identifier)
        }
    }

    Timer {
        id: movementTimer
        interval: 5000
        repeat: true
        running: true

        onTriggered: {
            var point = fishManager.getNewDestination(fish.identifier);
            x = point.x
            y = point.y
            console.log("got: x=" + point.x +" y=" + point.y)
        }
    }

    Behavior on x {
        NumberAnimation { duration: movementTimer.interval }
    }

    Behavior on y {
        NumberAnimation { duration: movementTimer.interval }
    }
}
