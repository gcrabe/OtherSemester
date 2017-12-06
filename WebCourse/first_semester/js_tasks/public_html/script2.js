/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

(function () {
    function RemoverChars(inputStr) {
        this._str = inputStr;
    }
    
    RemoverChars.prototype.removeChars = function () {
        var result = this._str;
        var matchArr = [];
        var matchPattern = /[^\s,\.,\,,\:,\;,\!,\?]+/gi;
        var firstWord = "";

        if (!/[^\s,\.,\,,\:,\;,\!,\?]+/i.test(result)) {
            return result;
        }
        
        matchArr = this._str.match(matchPattern);

        if (matchArr.length === 1) {
            return result;
        }
        
        firstWord = matchArr[0];

        for (var j = 0; j < firstWord.length; j++) {
            var searchChar = new RegExp(firstWord[j], "i");
            var count = 0;
            
            for (var i = 0; i < matchArr.length; i++) {
                if (searchChar.test(matchArr[i])) {
                    count++;
                }
            }

            if (count === matchArr.length) {
                result = result.replace(new RegExp(firstWord[j], "gi"), "");
            }

        }

        return result;
    };
    
    var str = prompt("exp", "Чего-с изволите-с?Барин-с!");
    var test = new RemoverChars(str);
    alert(test.removeChars());
})();