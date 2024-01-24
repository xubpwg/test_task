import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtCharts 2.15
import QtQuick.Dialogs 1.3
import my.WordCounter 1.0

Window {
    id: root

    width: 1200
    height: 600
    visible: true
    title: qsTr("Word Counter")

    required property WordCounter wordCounter

    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Button {
                id: openFileButton
                text: qsTr("Open File")
                onClicked: fDialog.open()
            }
            Button {
                id: stopProcessingButton
                text: qsTr("Stop Processing")
            }
        }

        ChartView {
            title: "Top 15 word count"
            legend.alignment: Qt.AlignBottom
            Layout.fillWidth: true
            Layout.fillHeight: true
            antialiasing: true

            BarSeries {
                id: mySeries

                axisX: BarCategoryAxis {
                    id: wordsAxis
                    categories: ["2007", "2008", "2009", "2010", "2011", "2012"]
                }

                BarSet {
                    label: "word count";
                    values: [2, 2, 3, 4, 5, 6]
                }
            }
        }
    }

    FileDialog {
        id: fDialog
        title: "Please choose a file"
        folder: shortcuts.documents
        nameFilters: [ "Text file (*.txt)" ]
        selectedNameFilter: nameFilters[0]
        onAccepted: wordCounter.startProcessing(fileUrl)
    }
}
