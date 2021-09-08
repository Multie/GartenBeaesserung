var defaultBorderBottomColor = "#DADADA";
var errorBorderBottomColor = "red";
var warnBorderBottomColor = "yellow";

function getChildenWithDataType(parent, tag, name) {
    var input = null;
    for (var a = 0; a < parent.children.length; a++) {
        if (parent.children[a].tagName == tag.toUpperCase() && parent.children[a].dataset.type == name) {
            input = parent.children[a];
            break;
        }
    }
    return input;
}
// Text
function sendTextClick(button) {
    var input = getChildenWithDataType(button.parentElement, "input", "text");
    if (!input.alt || !input.value) {
        input.style.borderBottomColor = errorBorderBottomColor;
        return;
    }
    sendValue(input.alt, input.value).then((newVal) => {
        input.value = newVal;
        input.style.borderBottomColor = defaultBorderBottomColor;
    }, (err) => {
        input.style.borderBottomColor = warnBorderBottomColor;
    });
}
// Number
function checkInput(input) {
    input.value = input.value.replace(/[^0-9]/g, "");
    var val = parseFloat(input.value);
    var min = parseFloat(input.min);
    var max = parseFloat(input.max);
    if (val < min) {
        input.style.borderBottomColor = errorBorderBottomColor;
        input.value = min;
        return false;
    } else if (val > max) {
        input.style.borderBottomColor = errorBorderBottomColor;
        input.value = max;
        return false;
    } else {
        return true;
    }
}

function sliderChange() {
    var ranges = document.querySelectorAll('input[type=range]');
    ranges.forEach(range => {
        var valueBox = document.getElementById(range.id + "value");
        valueBox.innerText = range.value;
    });
}

function sendNumberClick(button) {
    var input = getChildenWithDataType(button.parentElement, "input", "number");
    if (!input.alt || !input.value || !input.min || !input.max) {
        input.style.borderBottomColor = errorBorderBottomColor;
        return;
    }
    if (checkInput(input)) {
        sendValue(input.alt, input.value).then((newVal) => {
            input.value = newVal;
            input.style.borderBottomColor = defaultBorderBottomColor;
        }, (err) => {
            input.style.borderBottomColor = warnBorderBottomColor;
        });
    }
}

// Checkbox
function sendCheckboxClick(button) {
    var input = getChildenWithDataType(button.parentElement, "input", "checkbox");
    if (!input.alt || !input.checked) {
        input.style.borderBottomColor = errorBorderBottomColor;
        return;
    }
    sendValue(input.alt, input.checked).then((newVal) => {
        input.value = newVal;
        input.style.borderBottomColor = defaultBorderBottomColor;
    }, (err) => {
        input.style.borderBottomColor = warnBorderBottomColor;
    });
}
// Date
function sendDateClick(button) {
    var inputHour = getChildenWithDataType(button.parentElement, "input", "hour");
    var inputMin = getChildenWithDataType(button.parentElement, "input", "min");
    var inputSec = getChildenWithDataType(button.parentElement, "input", "sec");
    var inputDay = getChildenWithDataType(button.parentElement, "input", "day");
    var inputMon = getChildenWithDataType(button.parentElement, "input", "mon");
    var inputYear = getChildenWithDataType(button.parentElement, "input", "year");
    if (checkInput(inputHour) &&
        checkInput(inputMin) &&
        checkInput(inputSec) &&
        checkInput(inputDay) &&
        checkInput(inputMon) &&
        checkInput(inputYear)) {
        var date = `${pad(inputHour.value,2)}:${pad(inputMin.value,2)}:${pad(inputSec.value,2)} ${pad(inputDay.value,2)}.${pad(inputMon.value,2)}.${pad(inputYear.value,4)}`;
        sendValue(inputHour.alt, date).then((newVal) => {
            if (newVal.length == 19) {
                inputHour.value = newVal.substr(0, 2);
                inputMin.value = newVal.substr(3, 2);
                inputSec.value = newVal.substr(6, 2);
                inputDay.value = newVal.substr(9, 2);
                inputMon.value = newVal.substr(12, 2);
                inputYear.value = newVal.substr(15, 4);
                inputHour.style.borderBottomColor = defaultBorderBottomColor;
                inputMin.style.borderBottomColor = defaultBorderBottomColor;
                inputSec.style.borderBottomColor = defaultBorderBottomColor;
                inputDay.style.borderBottomColor = defaultBorderBottomColor;
                inputMon.style.borderBottomColor = defaultBorderBottomColor;
                inputYear.style.borderBottomColor = defaultBorderBottomColor;
            }

        }, (err) => {
            nputHour.style.borderBottomColor = warnBorderBottomColor;
            inputMin.style.borderBottomColor = warnBorderBottomColor;
            inputSec.style.borderBottomColor = warnBorderBottomColor;
            inputDay.style.borderBottomColor = warnBorderBottomColor;
            inputMon.style.borderBottomColor = warnBorderBottomColor;
            inputYear.style.borderBottomColor = warnBorderBottomColor;
        });
    }
}


function pad(num, size) {
    if (!num) {
        num = "";
    }
    var s = "0000" + num;
    return s.substr(s.length - size);
}
// Http
function sendValue(name, value) {
    return new Promise((resolve) => {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                resolve(xhttp.responseText);
            }
        };
        xhttp.open("POST", "rest/" + name, true);
        xhttp.send(value);
    });
}

function getValue(name) {
    return new Promise((resolve) => {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                resolve(xhttp.responseText);
            }
        };
        xhttp.open("GET", "rest/" + name, true);
        xhttp.send();
    });

}
// Reload Values and Toast
function reload() {
    var refreshs = document.querySelectorAll("[class=refresh]");
    refreshs.forEach(refresh => {
        getValue(refresh.alt).then(newVal => {
            refresh.innerHTML = newVal;
        });
    });
    var toasts = document.querySelectorAll("[class=toast]");
    toasts.forEach(toast => {
        getValue(toast.alt).then(newVal => {
            if (toast.value != newVal && newVal != "") {
                showToast(newVal);
            }
            toast.value = newVal;


        });
    });
}

setInterval(() => {
    reload();
}, 1000);
reload();

// Toast
function showToast(content) {
    var toast = document.createElement("DIV");
    toast.className = "snackbar show";
    toast.innerHTML = content;
    document.body.appendChild(toast);
    setTimeout(function() {
        document.body.removeChild(toast);
    }, 3000);
}

// Expandbox
function expandClick(button) {
    var div = getChildenWithDataType(button.parentElement, "div", "expand-content");
    var up = getChildenWithDataType(button, "div", "show");
    var down = getChildenWithDataType(button, "div", "hidden");
    if (div) {
        if (!div.style.maxHeight) {
            div.style.maxHeight = div.firstElementChild.clientHeight + "px";
            up.style.display = "";
            down.style.display = "none";
        } else {
            div.style.maxHeight = null;
            up.style.display = "none";
            down.style.display = "";
        }
    }


}