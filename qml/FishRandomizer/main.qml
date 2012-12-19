import QtQuick 2.0

import "fishCreation.js" as FishCreator

Rectangle {
    id: aquarium
    Image {
      anchors.centerIn: parent
      source: "background.svg"
    }

    MouseArea {
      acceptedButtons: Qt.RightButton
      anchors.fill: parent
      onClicked: FishCreator.createFish();
    }
}
