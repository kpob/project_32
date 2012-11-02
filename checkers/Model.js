/*
 * Potrzebne:
 * stan gry:
 * # isThisEnd?
 */

Model = function() {
	this.fields = [];
};

Model.prototype = {
	init : function() {
		for ( var i = 0; i < 32; i += 1) {
			this.fields[i] = new Field();
		}
		this.setFields("black", [ 31, 30, 29, 28, 27,26,25,24,23,22,21,20 ]);
		this.setFields("white", [ 0, 1, 2, 3, 4,5,6,7,8,9,10,11]);
	},

	setFields : function(color, fieldsArray) {
		if (color == "black") {
			for (i in fieldsArray) {
				this.fields[fieldsArray[i]].setBlack();
			}
		} else {
			for (i in fieldsArray) {
				this.fields[fieldsArray[i]].setWhite();
			}
		}
	},

	getFields : function() {
		return this.fields;
	},
	
	setNewGame : function(){
		//log("ustaw sie");
		this.setFields("black", [ 31, 30, 29, 28, 27,26,25,24,23,22,21,20 ]);
		this.setFields("white", [ 0, 1, 2, 3, 4,5,6,7,8,9,10,11]);
	}
};
