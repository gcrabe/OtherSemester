(function() {
	var function1 = function() {
		var type, i, j, res, temp;
		
		if (arguments.length == 0) {
			console.log("Error: no input arguments");
			return false;
		}
		
		type = typeof arguments[0];
		
		if (arguments.length > 1) {
			for (i = 0; i < arguments.length; i++) {
				if (arguments[i] === null) {
					console.log("Error: has null value");
					return false;
				}
				
				if (typeof(arguments[i]) != type) {
					console.log("Error: different types");
					return false;
				}
			}
		}
		
		if (type == "number" || type == "string") {
			res = (type == "number" ? 0 : "");
			
			for (i = 0; i < arguments.length; i++) {
				res += arguments[i];
			}
			
			console.log("Result: " + res);
			return true;
		}
		
		res = [];
		
		for (i = 0; i < arguments.length; i++) {
			if (typeof(arguments[i]) != "object") {
				console.log("Error: incorrect type");
				return false;
			}
			
			if (typeof(arguments[i] == "object")) {
				temp = arguments[i];
				
				if (!(temp.length >= 0)) {
					console.log("Error: object is not array");
					return false;
				}
				
				for (j = 0; j < temp.length; j++) {
					res.push(temp[j]);
				}
			}
		}
		
		console.log("Result: ")
		for (i = 0; i < res.length; i++) {
			console.log(res[i]);
		}
		
		return true;
	}
	/*
	function1();
	function1(1, 2, 4);
	function1(1, 2, null, 4);
	function1("str", 10);
	function1("str", "ing");
	function1([1, 2, 3], new Array(null, undefined), ["7", new Array("inserted")]);
	function1([], {a: true});
	*/
	
	var function2 = function() {
		var i, intPartStr, doublePartStr = "", cnt, negativeSign, res = "";
		
		if (arguments.length == 0) {
			return "Error: no input arguments";
		}
		
		for (i = 0; i < arguments.length; i++) {
			if (typeof arguments[i] != "number" || !isFinite(arguments[i])) {
				return "Error: argument is not a finite number";
			}
		}
		
		negativeSign = (arguments[0] < 0);
		
		intPartStr = Math.abs(arguments[0]).toString();
		
		if (arguments.length > 1) {
			doublePartStr = arguments[1] * Math.pow(10, - arguments[1].toString().length);
			doublePartStr = (Math.round(doublePartStr * 100) / 100).toFixed(2);
		}
		
		cnt = 0;
		
		for (i = intPartStr.length - 1; i >= 0; i--) {
			res += intPartStr[i];
			cnt++;
			
			if (cnt == 3) {
				res += " ";
				cnt = 0;
			}
		}
		
		if (negativeSign) {
			res += " -";
		}
		
		res = res.split('').reverse().join(''); 
		
		return res + doublePartStr;
	}
	
//	console.log(function2(-1234567,890));
	
	var function3 = function(input, str) {
		var i, temp;
		
		str = str.toLowerCase();
		
		for (i = 0; i < input.length; i++) {
			temp = input[i].toLowerCase();
			
			if (~temp.indexOf(str)) { // != -1
				return true;
			}
		}
		
		return false;
	}
	
//	console.log(function3(["aba", "caba"], "c"));
	
}).call(this);

(function() {
	
	var finalDate = new Date("2018-07-15"),
		year, month, day, hour, minute, second;
	
	function tick() {
		var timer = document.getElementById("timer"),
			curDate = new Date(),
			diffMiliseconds = finalDate - curDate,
			diffDate = new Date(diffMiliseconds),
		
		year = parseInt(diffDate.getFullYear()) - 1970;
		month = parseInt(diffDate.getMonth());
		day = parseInt(diffDate.getDay());
		hour = parseInt(diffDate.getHours());
		minute = parseInt(diffDate.getMinutes());
		second = parseInt(diffDate.getSeconds());
		
		timer.innerHTML = "Countdown to " + year + " years " 
						+ month + " months " + day + " days "
						+ hour + " hours " + minute + " minutes " 
						+ second + " seconds ramaining";
	}
	
	setInterval(tick, 1000);
	
}).call(this);

(function() {
	
	//
	
}).call(this);























