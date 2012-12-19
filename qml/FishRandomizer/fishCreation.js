function createFish() {
  console.log("Creating fish...");
  var fish = Qt.createComponent("Fish.qml");
  var sprite = fish.createObject(aquarium, {"x": 100, "y": 100});
  if (sprite == null) {
    // Error Handling
    console.log("Error creating fish object");
    return;
  }
  console.log("Succesfully created fish.");
}
