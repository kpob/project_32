Player = function() {
	this.controler = {};
	this.color = {};
	this.speed = 300;
	this.AI = {};
};

Player.prototype = {
	setControler : function(controler) {
		this.controler = controler;
	},

	// black or white
	setColor : function(color) {
		this.color = color;
	},
	
	setAI : function(AI){
		this.AI = AI;
	},
	
	makeMove : function(){
		var fields = this.controler.getFields();
		var moves = this.getMoves(fields);
		
		if(moves.length > 0){
			var moveNr = this.pickMove(fields, moves);
			
			var beatingList = [];
			//jeśli przynajmniej jednen ruch to bicie to mamy do czynienia
			//z samymi biciami
			if(moves[0].beating){
				for(i in moves[moveNr].beating){
					beatingList.push(moves[moveNr].beating[i].beat);
				}
			}
			this.move(fields, moves[moveNr].from, moves[moveNr].to, beatingList);
		} else {
			this.win();
		}
	},
	
	getMoves : function(fields){
		var moves;
		if (this.color == "white") {
			moves = Moves.getMovesForWhite(fields);
		}else{
			moves = Moves.getMovesForBlack(fields);
		}
		return moves;
	},
	
	move : function(fields, from, to, beatingList){
		if (this.color == "white") {
			Moves.moveWhite(fields, from, to, beatingList);
		}else{
			Moves.moveBlack(fields, from, to, beatingList);
		}
		this.controler.view.moveFigure(from, to);
		for(i in beatingList){
			this.controler.view.deleteFigure(beatingList[i]);
		}
	},
	
	win : function(){
		if (this.color == "white") {
			log("!!! BLACK WINS !!!");
		}else{
			log("!!! WHITE WINS !!!");
		}	
//		this.controler.model.listFields();
	},
	
	pickMove : function(fields, moves){
		var moveNr = this.AI.pickMove(fields, moves, this.color);
		return moveNr;
	}
};
