import QtQuick 2.0
import Fishes 1.0

Item {
    id: fish
    width: 150
    height: 100
    FishObj
    {
        id: internal
        startLimit.x: 0
        startLimit.y: 0
        endLimit.x: aquarium.width
        endLimit.y: aquarium.height

    }
    property int identifier: 0
    property int interval: 5000
    AnimatedImage {
        id: fishImage
        source: "animated-fish.gif"
        fillMode: Image.PreserveAspectFit
        width: fish.width
        height: fish.height
        mirror: false
        scale: 1
        MouseArea {
            acceptedButtons: Qt.RightButton
            onClicked: fishManager.fishClicked(mouseX,mouseY)
        }

        Component.onCompleted: {
            identifier = fishManager.registerFish(aquarium.width*scale-fish.width,aquarium.height*scale-fish.height);
            //movementTimer.triggeredOnStart = true
            console.log("Fish completed. Id = " + identifier)
        }
    }

    Timer {
        id: movementTimer
        interval: fish.interval
        repeat: true
        running: true

        onTriggered: {
            var point = internal.getNewDestination();
            if (point.x > x)
                fishImage.mirror = true
            else
                fishImage.mirror = false
            fish.state = 'swimming'
            x = point.x
            y = point.y
            console.log("Fish received new coordinates: x=" + point.x +" y=" + point.y)
        }
    }

    states: [
        State {
            name: "putting"
            PropertyChanges { target: fish; x: parent.width/2; y: parent.height/2 + fish.height }
        },
        State {
            name: "swimming"
            PropertyChanges { target: fish }
        }
    ]

    Behavior on x {
        NumberAnimation {
            duration: movementTimer.interval
        }
    }

    Behavior on y {
        NumberAnimation {
            duration: movementTimer.interval
        }
    }

    transitions: [
        // When putting fish into aquarium, use OutCubic animation over y
        Transition {
            to: "putting"
            NumberAnimation {
                properties: "y"
                easing.type: Easing.OutCubic
                duration: movementTimer.interval
            }
        }

    ]
}
