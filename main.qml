import QtQuick 2.12
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
import com.FileSyncMaster 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("PhotoSyncApp")

    signal startPressed(var _src,var _dest)
    signal startDryRun()
    signal startSync()
    property url sourceDirectory: ""
    property url destinationDirectory: ""
    property double lastSyncsDone: 0
    property double firstSyncsDoneTime: -1
    property double firstSyncsDoneCount: -1
    property double startTime: 0

    signal syncChanged(var syncDone,var syncTotal)
    signal syncChangedTotal(var syncDone,var syncTotal)
    signal initSrcDestDirectory(var srcDir,var destDir)

    onSyncChanged: {
        var newTime = new Date().getTime()
        if(firstSyncsDoneTime < 0) {
            firstSyncsDoneTime = newTime
        }
        progressBarRun.to = syncTotal
        progressBarRun.value = syncDone
        var picsPerSecond = Number(syncDone-firstSyncsDoneCount)/((newTime-firstSyncsDoneTime)/1000)
        progressTextRun.text = syncDone+"/"+syncTotal+" ("+picsPerSecond.toFixed(2)+" Pics/sec)"
        startTime = newTime
        lastSyncsDone = syncDone
    }

    onSyncChangedTotal: {
        progressBarTotal.to = syncTotal
        progressBarTotal.value = syncDone
        firstSyncsDoneCount = syncDone
        progressTextTotal.text = syncDone+"/"+syncTotal
    }

    onInitSrcDestDirectory: {
        sourceDirectory = srcDir
        destinationDirectory = destDir
    }

    GridLayout {
        anchors.centerIn: parent
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        columns: 2

        Button {
            Layout.columnSpan: 2
            FileDialog {
                id: sourceFileDialog
                title: "Please choose Source Directory"
                folder: sourceDirectory
                selectFolder: true
                selectExisting: true
                onAccepted: {
                    sourceDirectory = sourceFileDialog.folder
                }
            }
            id: selectSourceButton
            width: 100; height: 20;
            text: "Source: "+sourceDirectory

            onClicked: sourceFileDialog.open()
        }

        Button {
            Layout.columnSpan: 2
            FileDialog {
                id: destinationFileDialog
                title: "Please choose Destination Directory"
                folder: destinationDirectory
                selectFolder: true
                selectExisting: true
                onAccepted: {
                    destinationDirectory = destinationFileDialog.folder
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
            text: "Start Analyze"

            onClicked:startPressed(sourceDirectory,destinationDirectory)
        }
        Button {
            width: 100; height: 20;
            text: "Sync"

            onClicked:startSync()
        }

        GroupBox {
            Layout.columnSpan: 2
            implicitHeight: 70
            title: "Total Progress"
            Column {
                ProgressBar {
                    id: progressBarTotal
                    from: 0

                }
                Text {
                    id: progressTextTotal
                }
            }
        }

        GroupBox {
            Layout.columnSpan: 2
            implicitHeight: 70
            title: "Progress during current program run"
            Column {
                ProgressBar {
                    id: progressBarRun
                    from: 0

                }
                Text {
                    id: progressTextRun
                }
            }
        }
    }
}
