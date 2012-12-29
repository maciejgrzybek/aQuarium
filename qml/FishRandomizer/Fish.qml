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

        Component.onCompleted: {
            identifier = fishManager.registerFish(aquarium.width*scale-fish.width,aquarium.height*scale-fish.height);
            //movementTimer.triggeredOnStart = true
            console.log("Fish completed. Id = " + identifier)
        }
    }

    MouseArea {
        acceptedButtons: Qt.LeftButton
        anchors.fill: parent
        onClicked: {
            console.log("Fish clicked")
            // grow up TextEdit (nameBox)
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

    Rectangle
    {
        id: nameBox
        color: "red"
        width: nameEdit.paintedWidth
        height: nameEdit.paintedHeight
        //anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        anchors.topMargin: 5
        TextEdit {
            id: nameEdit
            height: parent.height
            width: parent.width
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            persistentSelection: false
            text: internal.name
            smooth: true
            cursorVisible: false
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
