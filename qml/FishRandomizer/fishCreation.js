var fish;
var sprite;
var fishCount = 0;

function createFish() {
  console.log("Creating fish...");
  fish = Qt.createComponent("Fish.qml");
  sprite = fish.createObject(aquarium, {"x": 100, "y": 100});
  if (sprite == null) {
    // Error Handling
    console.log("Error creating fish object");
    return;
  }
  fishCount++;
  console.log("Succesfully created " + fishCount + ". fish");
}
