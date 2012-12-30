import QtQuick 2.0

Item
{
    id: toolbar

    signal createButtonClicked
    signal randomButtonClicked

    Column {
        anchors.top: parent.top
        anchors.right: parent.left

        Button {
            id: createButton
            width: 140; height: 32
            text: "Create"
            purpleButton: true
            onClicked: toolbar.createButtonClicked()
        }

        Button {
            id: randomButton
            width: 140; height: 32
            text: "Random"
            onClicked: toolbar.randomButtonClicked()
        }
    }
}
