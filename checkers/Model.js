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
		// ustawienie pionków
		this.setFields("black", [12, 14]);
		this.setFields("white", [17, 19]);

//		this.setFields("black", [ 31, 30, 29, 28, 27, 26 ]);
//		this.setFields("white", [ 0, 1, 2, 3, 4, 5,6, 7,8]);
//		this.setFields("black", [ 27, 26 ]);
//		this.setFields("white", [ 8, 9, 10]);
		this.fields[12].setQueen();
		this.fields[14].setQueen();
		this.fields[17].setQueen();
		this.fields[19].setQueen();
//		this.fields[10].setQueen();
//		for(var i=0; i<14; i++)
//			this.fields[i].setQueen();
//		for(var i=15; i<32; i++)
//			this.fields[i].setQueen();
		// for(var i = 0; i < 32; i+=1){
		// this.fields[i].say();
		// }
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
	
	listFields : function(){
		log('s');
		var f = this.fields;
		for(i in f){
			log(i+" "+f[i].whoAmI());
		}
	}
};
