Player = function() {
	this.delay = 300;
	this.color = {};
	this.AI = {};
};

Player.prototype = {

	setColor : function(color) {
		this.color = color;
	},
	
	setAI : function(AI){
		this.AI = AI;
	},
	
	makeMove : function(fields){
		var move = this.AI.pickMove(fields, this.color);
		if(move){
			this.executeMove(fields, move);
		}else{
			log("Brak ruchów. GameOver");	
		}
	},

	executeMove : function(fields, move){
		var beatingList = [];
		if(move.beating){
			for(i in move.beating){
				beatingList.push(move.beating[i].beat);
			}
		}
		//poruszanie modelu
		Moves.move(fields, move.from, move.to, beatingList, this.color);
		//poruszanie view
		for(i in beatingList){
			checkers.view.deleteFigure(beatingList[i]);
		}
		checkers.view.moveFigure(move.from, move.to);

		//ruch dla nacl
		var movesForNacl = [];
		if(move.beating){
			for(j in move.beating){
				var beat = move.beating[j];
				if(j == 0){
					movesForNacl.push({
						f : move.from,
						t : beat.end
					});
				}else{
					var beatPrev = move.beating[j-1];
					movesForNacl.push({
						f : beatPrev.end,
						t : beat.end
					});
				}
			}
			var moveText = "move:"+movesForNacl[0].f+","+movesForNacl[0].t;
			for(var s=1; s<movesForNacl.length; s++){
				moveText = moveText + ","+movesForNacl[s].f+","+movesForNacl[s].t;
			}
			naclModule.postMessage(moveText);
		}else{
			naclModule.postMessage("move:"+move.from+","+move.to);
		}
	}
};
