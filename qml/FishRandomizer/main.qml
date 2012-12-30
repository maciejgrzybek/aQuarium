import QtQuick 2.0

import "fishCreation.js" as FishCreator

Item {
    id: aquarium
    Image {
      id: backgroundImage
      anchors.centerIn: parent
      width: aquarium.width
      height: aquarium.height
      fillMode: Image.PreserveAspectFit
      smooth: true
      source: "background.svg"
      scale: 1
    }

    MouseArea {
      acceptedButtons: Qt.LeftButton | Qt.RightButton
      anchors.fill: parent
      onClicked: {
          if (mouse.button == Qt.LeftButton)
          {
            fishManager.chooseWinningFish()
            aquarium.focus = true
          }
          else if (mouse.button == Qt.RightButton)
          {
            var fish = FishCreator.createFish()
            fish.focus = true
          }
      }
    }
}
