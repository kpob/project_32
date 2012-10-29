Moves = function() {
	this.map = [];
	for ( var i = 0; i < 32; i++) {
		this.map[i] = {
			currentPosition : i,
			upRightPosition : this.upRight(i),
			upLeftPosition : this.upLeft(i),
			downRightPosition : this.downRight(i),
			downLeftPosition : this.downLeft(i)
		};
	}
};

Moves.prototype = {
	getA : function() {
		log(this.a);
	},

	getMovesForWhite : function(fields) {
		return this.movesList(fields);
	},

	getMovesForBlack : function(fields) {
		var moves = this.movesList(this.rotateFields(fields));

		this.rotateFields(fields);
		return this.rotateMoves(moves);
	},

	rotateMoves : function(moves) {
		for (i in moves) {
			moves[i].from = 31 - moves[i].from;
			moves[i].to = 31 - moves[i].to;
			if(moves[i].beating){
				for(k in moves[i].beating){
					moves[i].beating[k].beat = 31 - moves[i].beating[k].beat;
					moves[i].beating[k].end = 31 - moves[i].beating[k].end;
				}
			}
		}
		return moves;
	},

	rotateFields : function(fields) {
		for (i in fields) {
			if (!fields[i].white && !fields[i].black) {

			} else if (fields[i].white) {
				fields[i].white = false;
				fields[i].black = true;
			} else if (fields[i].black) {
				fields[i].white = true;
				fields[i].black = false;
			}
		}
		return fields.reverse();
	},

	movesList : function(fields) {
		var moves = [];
/*
		for ( var i = 0; i < 32; i++) {
			// pionek musi byc biały
			if (fields[i].isWhite()) {
				// jeśli jest królową to ma więcej opcji
				if (fields[i].isQueen()) {
					// queen moves
					var newBeatPawnMoves = this.beatMoves(i, fields, true);
					concat(moves, newBeatPawnMoves);
				} else {
//					log("beatMoves: "+i);
					var newBeatPawnMoves = this.beatMoves(i, fields, false);
					concat(moves, newBeatPawnMoves);

				}
			}
		}
*/
		// nie znaleziono bicia
		if (moves.length == 0) {
			for ( var i = 0; i < 32; i++) {
				if (fields[i].isWhite()) {
					if (fields[i].isQueen()) {
						var newFreeQueenMoves = this.freeMoves(i, fields, true);
						concat(moves, newFreeQueenMoves);
					} else {
						var newFreePawnMoves = this.freeMoves(i, fields, false);
						// log("l: "+newFreePawnMoves.length);
						concat(moves, newFreePawnMoves);
					}
				}
			}
		}
		return moves;
	},

	// Ruchy pionków
	freeMoves : function(position, fields, queen) {
		var moves = [];
		var pawn = this.map[position];
		// Na lewo-góra.
		if (pawn.upLeftPosition) {
			var upLeftField = fields[pawn.upLeftPosition];
			if (upLeftField.isFree()) {
				moves[moves.length] = {
					from : pawn.currentPosition,
					to : pawn.upLeftPosition,
					beating : false
				};
			}
		}
		// Na prawo-góra.
		if (pawn.upRightPosition) {
			var upRightField = fields[pawn.upRightPosition];
			if (upRightField.isFree()) {
				moves[moves.length] = {
					from : pawn.currentPosition,
					to : pawn.upRightPosition,
					beating : false
				};
			}
		}
		// Jeśli jest to królowa to sprawdz ruchy w dół.
		if(queen){
			// Na lewo-dół.
			if (pawn.downLeftPosition) {
				var downLeftField = fields[pawn.downLeftPosition];
				if (downLeftField.isFree()) {
					moves[moves.length] = {
						from : pawn.currentPosition,
						to : pawn.downLeftPosition,
						beating : false
					};
				}
			}
			// Na prawo-dół.
			if (pawn.downRightPosition) {
				var downRightField = fields[pawn.downRightPosition];
				if (downRightField.isFree()) {
					moves[moves.length] = {
						from : pawn.currentPosition,
						to : pawn.downRightPosition,
						beating : false
					};
				}
			}
		}
		return moves;
	},

	beatMoves : function(position, fields, isQueen) {
		var moves = this.pawnBeatCheck(position, fields, [], isQueen);
//		log("ml: "+moves.length);
		for(i in moves){
			moves[i] = {
					from: position,
					to: moves[i][moves[i].length-1].end,
					beating: moves[i]
			};
		}
		return moves;
	},

	pawnBeatCheck : function(position, fields, move, isQueen) {
		var moves = [];
		var pawnPosition = this.map[position];
		var end = true;

		// Jeśli istnieją dwa pola po lewej przekątnej do góry
		if (pawnPosition.upLeftPosition
				&& this.map[pawnPosition.upLeftPosition].upLeftPosition) {

			var firstPosition = pawnPosition.upLeftPosition;
			var secondPosition = this.map[firstPosition].upLeftPosition;
		
			if (fields[firstPosition].isBlack() && fields[secondPosition].isFree()) {
				//można bić
				var newMove = jQuery.extend(true, [], move);
				var newFields = [];
				for(var i=0; i<32; i++){
					newFields[i] = jQuery.extend(true, [], fields[i]);
				}
				var thisMove = {
						beat: firstPosition,
						end: secondPosition
				};
				newMove.push(thisMove);
				
				this.moveWhite(newFields, position, secondPosition, [firstPosition]);

				concat(moves, this.pawnBeatCheck(secondPosition, newFields, newMove, isQueen));
				end = false;
			}	
		}
		
		if (pawnPosition.upRightPosition
				&& this.map[pawnPosition.upRightPosition].upRightPosition) {

			var firstPosition = pawnPosition.upRightPosition;
			var secondPosition = this.map[firstPosition].upRightPosition;
		
			if (fields[firstPosition].isBlack() && fields[secondPosition].isFree()) {
				//można bić
				var newMove = jQuery.extend(true, [], move);
				var newFields = [];
				for(var i=0; i<32; i++){
					newFields[i] = jQuery.extend(true, [], fields[i]);
				}
				var thisMove = {
						beat: firstPosition,
						end: secondPosition
				};
				newMove.push(thisMove);
				this.moveWhite(newFields, position, secondPosition, [firstPosition]);
				
				concat(moves, this.pawnBeatCheck(secondPosition, newFields, newMove, isQueen));
				end = false;
			}	
		}
		
		if(isQueen){
			// Jeśli istnieją dwa pola po lewej przekątnej do góry
			if (pawnPosition.downLeftPosition
					&& this.map[pawnPosition.downLeftPosition].downLeftPosition) {
	
				var firstPosition = pawnPosition.downLeftPosition;
				var secondPosition = this.map[firstPosition].downLeftPosition;
			
				if (fields[firstPosition].isBlack() && fields[secondPosition].isFree()) {
					//można bić
					var newMove = jQuery.extend(true, [], move);
					var newFields = [];
					for(var i=0; i<32; i++){
						newFields[i] = jQuery.extend(true, [], fields[i]);
					}
					var thisMove = {
							beat: firstPosition,
							end: secondPosition
					};
					newMove.push(thisMove);
					
					this.moveWhite(newFields, position, secondPosition, [firstPosition]);
	
					concat(moves, this.pawnBeatCheck(secondPosition, newFields, newMove, isQueen));
					end = false;
				}	
			}
			
			if (pawnPosition.downRightPosition
					&& this.map[pawnPosition.downRightPosition].downRightPosition) {
	
				var firstPosition = pawnPosition.downRightPosition;
				var secondPosition = this.map[firstPosition].downRightPosition;
			
				if (fields[firstPosition].isBlack() && fields[secondPosition].isFree()) {
					//można bić
					var newMove = jQuery.extend(true, [], move);
					var newFields = [];
					for(var i=0; i<32; i++){
						newFields[i] = jQuery.extend(true, [], fields[i]);
					}
					var thisMove = {
							beat: firstPosition,
							end: secondPosition
					};
					newMove.push(thisMove);
					this.moveWhite(newFields, position, secondPosition, [firstPosition]);
					
					concat(moves, this.pawnBeatCheck(secondPosition, newFields, newMove, isQueen));
					end = false;
				}	
			}
		}
		
		if(end){
			if(move.length > 0)
				moves.push(move);
		}
		return moves;
	},
	
	//Ruchy damek

	// Static tools
	// Obliczanie pozycji
	upRight : function(position) {
		var ur;
		if (position > 27)
			ur = false;
		else if (position % 8 == 7)
			ur = false;
		else {
			if (Math.floor(position / 4) % 2 == 0)
				ur = position + 4;
			else
				ur = position + 5;
		}
		return ur;
	},

	upLeft : function(position) {
		var ul;
		if (position > 27)
			ul = false;
		else if (position % 8 == 0)
			ul = false;
		else {
			if (Math.floor(position / 4) % 2 == 0)
				ul = position + 3;
			else
				ul = position + 4;
		}
		return ul;
	},

	downRight : function(position) {
		var dr;
		if (position < 4)
			dr = false;
		else if (position % 8 == 7)
			dr = false;
		else {
			if (Math.floor(position / 4) % 2 == 0)
				dr = position - 4;
			else
				dr = position - 3;
		}
		return dr;
	},

	downLeft : function(position) {
		var dr;
		if (position < 4)
			dr = false;
		else if (position % 8 == 0)
			dr = false;
		else {
			if (Math.floor(position / 4) % 2 == 0)
				dr = position - 5;
			else
				dr = position - 4;
		}
		return dr;
	},

	moveWhite : function(fields, from, to, beatList) {
		if(fields[from].isQueen() || to == 31 || to == 30 || to == 29 || to == 28){
			fields[to].setQueen();
		}
		
		fields[from].setFree();
		fields[to].setWhite();
		
		this.deletePawns(fields, beatList);
	},

	moveBlack : function(fields, from, to, beatList) {
		if(fields[from].isQueen() || to == 0 || to == 1 || to == 2 || to == 3){
			fields[to].setQueen();
		}
		fields[from].setFree();
		fields[to].setBlack();
		this.deletePawns(fields, beatList);
	},
	
	deletePawns : function(fields, beatList) {
		if(beatList){
			for(i in beatList){
				fields[beatList[i]].setFree();
			}
		}
	}
};

var Moves = new Moves();
