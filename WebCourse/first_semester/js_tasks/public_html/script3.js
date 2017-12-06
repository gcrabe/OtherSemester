/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

(function () {
    var text = document.getElementById('Text'),
        color = document.getElementById('Color'),
        type = document.getElementById('Type');

    var createButton = document.getElementById('CreateButton'),
        changeButton = document.getElementById('ChangeButton'),
        deleteButton = document.getElementById('DeleteButton');

    var list = document.getElementById('list');

    var currentElement;
    var nodesList = [];

    createButton.onclick = function () {
        var li = document.createElement('li');

        li.innerHTML = text.value;
        li.style.color = color.value;
        li.style.listStyle = type.value;

        li.onclick = function () {
            for (var i = 0; i < nodesList.length; i++) {
                nodesList[i].style.border = '0 solid blue';
            }

            this.style.border = '1px solid blue';
            text.value = this.innerHTML;
            type.value = this.style.listStyle;
            color.value = this.style.color;
            currentElement = this;
        };

        nodesList.push(li);
        list.appendChild(li);
    };


    deleteButton.onclick = function () {
        list.removeChild(currentElement);
    };

    changeButton.onclick = function () {
        currentElement.innerHTML = text.value;
        currentElement.style.color = color.value;
        currentElement.style.listStyle = type.value;
    };
})();