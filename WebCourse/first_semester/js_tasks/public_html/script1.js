;
(function () {
    function CalculateString(inputStr) {
        this._str = inputStr;
    }
    CalculateString.prototype.calc = function () {
        var result = 0;
        var matchArr = [];
        var searchPattern = /\-?\d+(\.\d+)?|[\+,\-,\*,\/,\=]{1}/ig;

        matchArr = this._str.match(searchPattern);

        if (matchArr[0] * 1 + "" !== "NaN") {
            result += matchArr[0] * 1;
        }

        for (var i = 0; i < matchArr.length; i++) {
            switch (matchArr[i]) {
                case "+":
                    result += matchArr[i + 1] * 1;
                    break;
                case "-":
                    result -= matchArr[i + 1] * 1;
                    break;
                case "*":
                    result *= matchArr[i + 1] * 1;
                    break;
                case "/":
                    result /= matchArr[i + 1] * 1;
                    break;
                case "=":
                    break;
                default:
                    continue;
                    break;
            }
        }

        return result;
    }

    var str = prompt("exp", "3.5 землекопа +4 поросенка *10 рублей - 5.5 $ /5 человек =");
    var test = new CalculateString(str);
    alert(test.calc());
})();