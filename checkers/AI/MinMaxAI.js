MinMaxAI = function(){
	this.depth = 1;
};

MinMaxAI.prototype = {
		pickMove : function(fields, color){
			var moves = Moves.getMoves(fields, color);
			var bestValue = -1000;
			var bestMove;	
			for(m in moves){
				var move = moves[m];
				var newFields = [];
				for(var i=0; i<32; i++){
					newFields[i] = jQuery.extend(true, [], fields[i]);
				}
				var beatingList = [];
				if(move.beating){
					for(k in move.beating){
						beatingList.push(move.beating[k].beat);
					}
				}
				Moves.move(newFields, move.from, move.to, beatingList, color);
				var value = this.minMax(newFields, Moves.opositColor(color), this.depth);
				if(value > bestValue){
					bestValue = value;
					bestMove = move;
				}
			}

			return bestMove;
		},

		minMax : function(fields, color, depth){
			var moves = Moves.getMoves(fields, color);
			var bestValue = -1000;
			for(m in moves){
				var move = moves[m];
				var newFields = [];
				for(var i=0; i<32; i++){
					newFields[i] = jQuery.extend(true, [], fields[i]);
				}
				var beatingList = [];
				if(move.beating){
					for(k in move.beating){
						beatingList.push(move.beating[k].beat);
					}
				}
				Moves.move(newFields, move.from, move.to, beatingList, color);
				var value;				
				if(depth == 0)				
					value = this.evaluation(newFields, color);
				else value = this.minMax(newFields, Moves.opositColor(color), depth-1);		
				if(value > bestValue){
					bestValue = value;
				}
			}
			return bestValue;			
		},

		evaluation : function(fields, color){
			// wyliczam wynik dla białego
			var value = 0;
			for(i in fields){
				var field = fields[i];
				if(field.isWhite()){
					if(field.isQueen()){
						value += 3;
					}else{
						value += 1;		
					}
				} else if (field.isBlack()){
					if(field.isQueen()){
						value -= 3;
					}else{
						value -= 1;		
					}
				}
			}
			if(color == "white"){
				return value;			
			}else{
				return -value;			
			}
		}
};
