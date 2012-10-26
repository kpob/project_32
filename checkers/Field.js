Field = function() {
	this.white = false;
	this.black = false;
	this.queen = false;
};

Field.prototype = {
		
		isWhite : function(){
			if(this.white)
				return true;
			return false;
		},
		
		isBlack : function(){
			if(this.black)
				return true;
			return false;
		},
		
		isFree : function() {
			if(!this.black && !this.white)
				return true;
			return false;
		},
		
		isQueen : function(){
			if(this.queen)
				return true;
			return false;
		},
		
		setWhite : function(){
			this.white = true;
			this.black = false;
		},
		
		setBlack : function(){
			this.white = false;
			this.black = true;
		},
		
		setFree : function() {
			this.white = false;
			this.black = false;
			this.queen = false;
		},
		
		setQueen : function() {
			this.queen = true;
		},
		
		whoAmI : function(){
			if(this.isWhite())
				return 'white';
			if(this.isBlack())
				return "black";
			if(this.isFree())
				return "free";
		}
};