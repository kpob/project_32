function pp(obj) {
	log(prettyPrint(obj));
}

function prettyPrint(obj) {
	var toString = Object.prototype.toString, newLine = "\n", space = " ", tab = 4, buffer = "",
	// Second argument is indent
	indent = arguments[1] || 0,
	// For better performance, Cache indentStr for a given indent.
	indentStr = (function(n) {
		var str = "";
		while (n--) {
			str += space;
		}
		return str;
	})(indent);

	if (!obj || (typeof obj != "object" && typeof obj != "function")) {
		// any non-object ( Boolean, String, Number), null, undefined, NaN
		buffer += obj;
	} else if (toString.call(obj) == "[object Date]") {
		buffer += "[Date] " + obj;
	} else if (toString.call(obj) == "[object RegExp") {
		buffer += "[RegExp] " + obj;
	} else if (toString.call(obj) == "[object Function]") {
		buffer += "[Function] " + obj;
	} else if (toString.call(obj) == "[object Array]") {
		var idx = 0, len = obj.length;
		buffer += "[" + newLine;
		while (idx < len) {
			buffer += [ indentStr, idx, ": ",
					prettyPrint(obj[idx], indent + tab) ].join("");
			buffer += "\n";
			idx++;
		}
		buffer += indentStr + "]";
	} else { // Handle Object
		var prop;
		buffer += "{" + newLine;
		for (prop in obj) {
			buffer += [ indentStr, prop, ": ",
					prettyPrint(obj[prop], indent + tab) ].join("");
			buffer += newLine;
		}
		buffer += indentStr + "}";
	}

	return buffer;
}

function log(text) {
	if (text)
		$('#logField').append(text + "\n");
	else
		$('#logField').append("\n");
}

function relative_complement(A, B) {
	return A.filter(function(elem) {
		return B.indexOf(elem) == -1;
	});
}

function symmetric_difference(A, B) {
	return concat(relative_complement(A, B), relative_complement(B, A));
}

function concat(arr1, arr2) {
	for (i in arr2)
		arr1.push(arr2[i]);
	return arr1;
}