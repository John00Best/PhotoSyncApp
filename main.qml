import QtQuick 2.12
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    signal startPressed(var _src,var _dest);
    property url sourceDirectory: ""
    property url destinationDirectory: ""


GridLayout {
    anchors.centerIn: parent
    columns: 1

   Button {
       FileDialog {
          id: sourceFileDialog
          title: "Please choose Source Directory"
          //folder: shortcuts.home
          selectFolder: true
          selectExisting: true
          onAccepted: {
              console.log("You chose sourceFileDialog: " + sourceFileDialog.folder)
              sourceDirectory = sourceFileDialog.folder

            }
       }
       id: selectSourceButton
       width: 100; height: 20;
       text: "Source: "+sourceDirectory

       onClicked: sourceFileDialog.open()
   }

   Button {
       FileDialog {
          id: destinationFileDialog
          title: "Please choose Destination Directory"
          //folder: shortcuts.home
          selectFolder: true
          selectExisting: true
          onAccepted: {
              destinationDirectory = destinationFileDialog.folder
              console.log("You chose destinationDirectory: " + destinationDirectory)
            }
       }

       id: selectDestinationButton
       width: 100; height: 20;
       text: "Destination: "+destinationDirectory

       onClicked: destinationFileDialog.open()
   }

  Button {
      id: startButton
      width: 100; height: 20;
      text: "Start"

      onClicked:startPressed(sourceDirectory,destinationDirectory)
  }
}


}
