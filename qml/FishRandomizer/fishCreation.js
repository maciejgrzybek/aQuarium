function createFish() {
  console.log("Creating fish...");
  var fishComponent = Qt.createComponent("Fish.qml");
  var fishObj = fishComponent.createObject(aquarium, {"x": aquarium.width/2, "y": 0});
  if (fishObj === null) {
    // Error Handling
    console.log("Error creating fish object");
    return;
  }
  fishObj.state = 'putting';
  console.log("Succesfully created fish.");
  return fishObj;
}
