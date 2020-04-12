import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    signal startPressed();


  Button {
      id: startButton
      anchors.centerIn: parent
      width: 100; height: 20;
      text: "Start"

      onClicked: startPressed()
  }


}
