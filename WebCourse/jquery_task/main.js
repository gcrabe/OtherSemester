(function() {
	var dataIdCounter = 5;

	function Student(id, firstName, midName, lastName, email, dateBirth, gender, course) {
		this.id = +id;
		this.firstName = firstName;
		this.midName = midName;
		this.lastName = lastName;
		this.email = email;
		this.dateBirth = new Date(Date.parse(dateBirth));
		this.gender = (gender == "male" || gender == "муж.") ? "муж." : "жен.";
		this.course = Number(course);
	}

	var students = [
		new Student(
			0,
			"Анисимов", 
			"Владимир", 
			"Гаврилович", 
			"avg@ro.ru", 
			"1993-02-4", 
			"муж.", 
			"5"
		),
		new Student(
			1,
			"Беспалов", 
			"Александр", 
			"Александрович", 
			"baa@ro.ru", 
			"1994-05-07", 
			"муж.", 
			"4"
		),
		new Student(
			2,
			"Бортников", 
			"Александр", 
			"Васильевич", 
			"bav@ro.ru", 
			"1997-01-06", 
			"муж.",
			"1"
		),
		new Student(
			3,
			"Булавин", 
			"Владимир", 
			"Иванович", 
			"bvi@ro.ru", 
			"1996-12-10", 
			"муж.", 
			"2"
		),
		new Student(
			4,
			"Буравлёв", 
			"Сергей", 
			"Михайлович", 
			"bsm@ro.ru", 
			"1995-11-08", 
			"муж.", 
			"3"
		)
	];

	var write = function write() {
		var trLine = "";

		for (var i = 0; i < students.length; i += 1) {
			trLine += '<tr class="tr_line" data-id="' + students[i].id + '">';

			for (var part in students[i]) {
				trLine += (part != "id" ? "<td>" + students[i][part]  + "</td>" : "");
			}
			
			trLine += "</tr>";
		}

		$("tbody").empty();
		$("tbody").html(trLine);
	}

	var reset = function reset() {
		var lines = $(".tr_line");

		for (var line of lines) {
			$(line).removeClass("selected");
		}
	};

	var resetFields = function resetFields() {
		$("#modal_first_name").val("");
		$("#modal_mid_name").val("");
		$("#modal_last_name").val("");
		$("#modal_email").val("");
		$("#modal_date_birth").val("");
		$("#modal_course").val("");
	};

	var getAvaliableNames = function getAvaliableNames() {
		var result = [];

		for (var i = 0; i < students.length; i++) {
			result.push(students[i].firstName);
			result.push(students[i].midName);
			result.push(students[i].lastName);
		}

		return result;
	};

	$(document).ready(function() {
		write();

		$("#main_data_table").DataTable();
		$("#modal_date_birth").datepicker();

		$("input[type='search']").attr("id", "search_input");

		var avaliableNames = getAvaliableNames();

		$("#search_input").autocomplete({
			source: avaliableNames
		});

		// $.validator.addClassRules({
		// 	EmailValidation: {
		// 		email: true
		// 	}
		// });

		$("#modal_form").validate({
			rules: {
				modal_first_name: {
					maxlength: 15,
					required: true
				},
				modal_mid_name: {
					maxlength: 15,
					required: true
				},
				modal_last_name: {
					maxlength: 15,
					required: true
				},
				modal_email: {
					email: true
				},
				modal_course: {
					number: true,
					min: 1,
					max: 6
				},
				modal_date_birth: {
					date: true
				}
			}
		});
	});

	$("#add_label").on("click", function() {
		resetFields();
	});

	$("#modal_button").on("click", function() {
		$("#modal_button").empty();
		$("#modal_button").html("Add new item");

		var first_name = $("#modal_first_name").val(),
			mid_name = $("#modal_mid_name").val(),
			last_name = $("#modal_last_name").val(),
			email = $("#modal_email").val(),
			date_birth = $("#modal_date_birth").val(),
			gender = $("#modal_gender").val(),
			course = $("#modal_course").val();

		students.push(new Student(
			dataIdCounter++,
			first_name,
			mid_name,
			last_name,
			email,
			date_birth,
			gender,
			course
		));

		write();
	});

	$("table").on("click", "tr", function() {
		var isSelected = $(this).hasClass("selected");

		reset();

		if (!isSelected) {
			$(this).addClass("selected");
		}
	});

	$("#delete_label").on("click", function() {
		var curElement = $(".selected")[0],
			dataId = $(curElement).attr("data-id");

			for (var student of students) {
				if (student.id == dataId) {
					students.splice(students.indexOf(student), 1);
				}
			}

		write();
	});

	$("#edit_label").on("click", function() {
		$("#modal_button").empty();
		$("#modal_button").html("Accept changes");

		var curElement = $(".selected")[0],
			dataId = $(curElement).attr("data-id");

		var student = null, studentId = -1;

		for (var i = 0; i < students.length; i++) {
			if (students[i].id == dataId) {
				student = students[i];
				studentId = i;
			}
		}

		var strYear = student.dateBirth.getFullYear().toString(),
			strMonth = (student.dateBirth.getMonth() + 1).toString(),
			strDay = student.dateBirth.getDate().toString();

		if (strMonth.length < 2) {
			strMonth = "0" + strMonth;
		}

		if (strDay.length < 2) {
			strDay = "0" + strDay;
		}

		var dateBirth = strYear + "-" + strMonth + "-" + strDay;
		
		$("#modal_first_name").val(student.firstName);
		$("#modal_mid_name").val(student.midName);
		$("#modal_last_name").val(student.lastName);
		$("#modal_email").val(student.email);
		$("#modal_date_birth").val(dateBirth);
		$("#modal_course").val(student.course);

		if (student.gender == "муж.") {
			$("#modal_gender_male").attr("selected", "selected");
		} else {
			$("#modal_gender_female").attr("selected", "selected");
		}
		
		var mods = document.querySelectorAll('.modal > [type=checkbox]');

    	[].forEach.call(mods, function(mod) { 
    		mod.checked = true; 
    	});
	});

}).call(this);