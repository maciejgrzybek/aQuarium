import QtQuick 2.0
import Fishes 1.0

Item {
    id: fish
    width: 150
    height: 100
    onFocusChanged: nameBox.forceActiveFocus()
    property int identifier: 0
    property int interval: 5000

    FishObj
    {
        id: internal
        startLimit.x: 0
        startLimit.y: 0
        endLimit.x: aquarium.width
        endLimit.y: aquarium.height
    }

    AnimatedImage {
        id: fishImage
        source: "animated-fish.gif"
        fillMode: Image.PreserveAspectFit
        width: fish.width
        height: fish.height
        mirror: false
        scale: 1

        Component.onCompleted: {
            identifier = fishManager.registerFish();
            internal.identifier = identifier
            console.log("Fish completed. Id = " + identifier)
        }
    }

    MouseArea {
        acceptedButtons: Qt.LeftButton
        anchors.fill: parent
        onClicked: {
            console.log("Fish clicked")
            if (nameBox.state == "grown")
            {
                nameBox.focus = false
            }
            else
            {
                nameBox.focus = true
            }
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
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        anchors.topMargin: 5
        onFocusChanged: nameEdit.forceActiveFocus()

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

        Behavior on scale {
            SmoothedAnimation {
                duration: 300
                velocity: 1.0
            }
        }

        states: [
            State {
                name: "normal"
                when: !nameEdit.activeFocus
                PropertyChanges { target: nameBox; scale: 1.0 }
            },
            State {
                name: "grown"
                when: nameEdit.activeFocus
                PropertyChanges { target: nameBox; scale: 7.0 }
            }
        ]
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
