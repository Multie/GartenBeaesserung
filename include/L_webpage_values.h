#ifndef L_WEBPAGE_VALUE_H
#define L_WEBPAGE_VALUE_H
#include <Arduino.h>

// Colum: content
String htmlColumn = F(R"###(
<div class="coloums">[[content]]</div>
)###");
// Row: content
String htmlRow = F(R"###(
<div class="rows">[[content]]</div>
)###");
// Text: text
String htmlText = F(R"###(
<div class="item text" tag="text">[[text]]</div>
)###");
// Button: label, name, value
String htmlButton = F(R"###(
<button class="item button" onclick="sendValue('[[name]]','[[value]]')"><div class="material-icons icon">send</div><div>[[label]]</div></button>
)###");
// Link: label, link
String htmlLink = F(R"###(
<a class="item button" href="[[link]]"><div class="material-icons icon">link</div><div>[[label]]</div></a>
)###");
// Item: label, value
String htmlItem = F(R"###(
<div class="item value"><div class="label">[[label]]</div><div class="content">[[value]]</div></div>
)###");
// Item Value: label, value
String htmlItemValue = F(R"###(
div class="reload" alt="[[name]]"></div>
)###");
// Item Input Text: disabled, name, value
String htmlItemInputText = F(R"###(
<input [[disabled]] type="text" name="text" alt="[[name]]" value="[[value]]">
<button class="icon [[disabled]]" onclick="sendTextClick(this)"><div class="material-icons icon">redo</div></button>
)###");
// Item Input Number: disabled, name, value, min, max
String htmlItemInputNumber = F(R"###(
<input [[disabled]] type="number" name="number" alt="[[name]]" value="[[value]]" min="[[min]]" max="[[max]]">
<button class="icon [[disabled]]" onclick="sendNumberClick(this)"><div class="material-icons">redo</div></button>
)###");
// Item Input Slider: disabled, name, value, min, max
String htmlItemInputSlider = F(R"###(
<div id="slider[[name]]value"></div>
<input [[disabled]] type="number" name="number" alt="[[name]]" value="[[value]]" min="[[min]]" max="[[max]]" onmousemove="sliderChange()">
<button class="icon [[disabled]]" onclick="sendNumberClick(this)"><div class="material-icons">redo</div></button>
)###");
// Item Input Checkbox: disabled, name, value
String htmlItemInputCheckbox = F(R"###(
<input [[disabled]] type="checkbox" name="checkbox" alt="[[name]]" checked="[[value]]">
<button class="icon [[disabled]]" onclick="sendCheckboxClick(this)"><div class="material-icons">redo</div></button>
)###");
// Item Input Date: disabled, name, valueHour, valueMin, valueSec, valueDay, valueMon, valueYear
String htmlInputDate = F(R"###(
<input [[disabled]] name="hour" alt="[[name]]" class="input-date" type="number" placeholder="Hour" value="[[valueHour]]" min="-1" max="59">
<input [[disabled]] name="min" alt="[[name]]" class="input-date" type="number" placeholder="Minute" value="[[valueMin]]" min="-1" max="59">
<input [[disabled]] name="sec" alt="[[name]]" class="input-date" type="number" placeholder="Second" value="[[valueSec]]" min="-1" max="23">
<input [[disabled]] name="day" alt="[[name]]" class="input-date" type="number" placeholder="Day" value="[[valueDay]]" min="-1" max="31">
<input [[disabled]] name="mon" alt="[[name]]" class="input-date" type="number" placeholder="Month" value="[[valueMon]]" min="-1" max="12">
<input [[disabled]] name="year" alt="[[name]]" class="input-date" type="number" placeholder="Year" value="[[valueYear]]" min="-1" max="9999">
<button class="icon [[disabled]]" onclick="sendDateClick(this)"><div class="material-icons">redo</div></button>
)###");

// Toast: name, value
String htmlToast = F(R"###(
<div class="toast" alt="[[name]]" value="[[value]]"></div>
)###");
// Expandable label, content
String htmlExpandableStart = F(R"###(
<div class="expand"><button class="item button" onclick="expandClick(this)"><div class="expandTitle">[[label]]</div><div data-type="hidden" class="material-icons icon">expand_more</div><div style="display:none;" data-type="show" class="material-icons icon">expand_less</div></button><div class="expandContent" data-type="expand-content close"><div>
)###");
String htmlExpandableEnd = F(R"###(
</div></div></div>
)###");
// Page: title, content
String htmlPageStart = F(R"###(
<!DOCTYPE html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1.0"><link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet"><link href="styles.min.css" rel="stylesheet"></head><body><div class="title">[[title]]</div><div class="content">
)###");

String htmlPageEnd = F(R"###(
</div><script src="script.min.js"></script></body>
)###");
#endif