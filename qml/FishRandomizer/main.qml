import QtQuick 2.0

import "fishCreation.js" as FishCreator

Item {
    id: aquarium
    Image {
      id: backgroundImage
      anchors.centerIn: parent
      fillMode: Image.PreserveAspectFit
      width: aquarium.width
      height: aquarium.height
      source: "background.svg"
      scale: 1
    }

    MouseArea {
      acceptedButtons: Qt.RightButton
      anchors.fill: parent
      onClicked: FishCreator.createFish()
    }
}
