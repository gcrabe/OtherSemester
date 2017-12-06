(function() {
	var text = document.getElementById("text_input"),
		color = document.getElementById("color_input"),
		type = document.getElementById("type_input");

	var createButton = document.getElementById("create_btn"),
		changeButton = document.getElementById("change_btn"),
		deleteButton = document.getElementById("delete_btn");

	var list = document.getElementById("list");

	var curElement = null;

	createButton.addEventListener("click", function() {
		var element = document.createElement("li");
		
		element.innerHTML = text.value;
		element.style.color = color.value;
		element.style.listStyle = type.value;
		
		list.appendChild(element);
	});

	changeButton.addEventListener("click", function() {

	});

	deleteButton.addEventListener("click", function() {
		//
	});
}).call(this);