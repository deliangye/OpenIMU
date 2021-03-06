import QtQuick 2.5
import QtQuick.Window 2.2
import InputNodeInt 1.0
import InputNodeDouble 1.0
import InputNodeString 1.0
import OutputNodeInt 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import jbQuick.Charts 1.0

Rectangle{
    width:parent.width;
    height:parent.height;
    anchors.centerIn: parent;

    Label{
        InputNodeInt{
            id: inputValue;
        }
        id: label_value
         property string id: "label_value";
        text: "Multiplier value: "+ inputValue.value[0]
        y:0
}
    Label {
       y:0
       x: parent.width/2-150
       text: "Données acquises par l'accéléromètre"
       font.pixelSize: 22
       color: "steelblue"
     }

    Label {
       id: test
       y:40
       x:parent.width/2-80
       font.pixelSize: 18
       color: "steelblue"
     }

    Chart{
        y:80
        //identity and internal maping
        id: chart_line;
        property string id: "chart_line";
        InputNodeString{
            id: labels;
        }
        InputNodeInt{
            id: input1;
        }

        //ui properties
        width:parent.width;
        height:parent.height-100;

        chartType: Charts.ChartType.LINE;
        chartData: {
            'labels':labels.value,
            'datasets':[
                {'fillColor': "rgba(0,128,128,0)",'pointColor': "rgba(255,0,0,1)",'strokeColor': "rgba(255,0,0,1)",'data': input1.value},
            ]
        };

        chartAnimated: true;
        chartAnimationEasing: Easing.InOutElastic;
        chartAnimationDuration: 500;

        chartOptions: {"segmentStrokeColor": "#ECECEC", "bezierCurve": true , "pointDot":true , "showScale": true,"scaleFontSize": 12 };
    }

    Label {
        y : parent.height -20
        x : 0
       text: "Tranche horaire: "
       font.pixelSize: 14
       color: "steelblue"
     }

    Slider {
        id: slider
        property string id: "slider";
        InputNodeInt{
            id: inputSliderMinimumValue;
        }
        InputNodeInt{
            id: inputSliderMaximumValue;
        }
        OutputNodeInt{
            id: outputSliderValue;
        }
        width: parent.width -225
        y : parent.height -20
        x : 125
        minimumValue: inputSliderMinimumValue.value[0]
        maximumValue: inputSliderMaximumValue.value[0]
        stepSize: 1
        onValueChanged:{
            test.text = "De " + value.toPrecision(3) +" h à  "+ maximumValue + " h"
            outputSliderValue.value[0] = value
        }
    }

}


