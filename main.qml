import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtCharts 2.15
import QtQuick.Dialogs 1.3
import my.wc 1.0

Window {
    id: root

    width: 1200
    height: 600
    visible: true
    title: qsTr("Word Counter")

    required property WCController controller

    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Button {
                id: openFileButton
                text: qsTr("Open File")
                onClicked: fDialog.open()
            }
            Button {
                id: resetButton
                text: qsTr("Reset Progress")
                onClicked: controller.resetProcessing()
            }
        }
        FileDialog {
            id: fDialog
            title: "Please choose a file"
            folder: shortcuts.documents
            nameFilters: [ "Text file (*.txt)" ]
            selectedNameFilter: nameFilters[0]
            onAccepted: controller.startProcessing(fileUrl)
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
                    id: xAxis
                }

                axisY: ValueAxis {
                    id: yAxis
                    min: 0.0
                    max: controller.topCount
                }

                BarSet {
                    id: mySeriesBarSet
                    label: "word count";
                }
            }
        }
    }

    Connections {
        target: controller

        function onTopWordsChanged() {
            xAxis.categories = controller.topWords
        }

        function onTopWordsCountChanged() {
            mySeriesBarSet.values = controller.topWordsCount
        }
    }


}
