function createFish() {
  console.log("Creating fish...");
  var fish = Qt.createComponent("Fish.qml");
  var sprite = fish.createObject(aquarium, {"x": aquarium.width/2, "y": 0});
  if (sprite === null) {
    // Error Handling
    console.log("Error creating fish object");
    return;
  }
  sprite.y = aquarium.height/2+sprite.height
  console.log("Succesfully created fish.");
}
