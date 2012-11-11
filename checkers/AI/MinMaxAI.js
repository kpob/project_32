MinMaxAI = function(){
	this.depth = 4;
	this.count = 0;
};

MinMaxAI.prototype = {
		pickMove : function(fields, color){
			var start = new Date();
			this.count = 0;
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
				var value = this.minMax(newFields, Moves.opositColor(color), this.depth, false);
				if(value > bestValue){
					bestValue = value;
					bestMove = move;
				}
			}
			var end = new Date();
			var time = end.getTime() - start.getTime();
			log("Przeszukane: "+this.count+"\nCzas: "+time/1000+"s \nCzas na 1 ruch: "+time/this.count+"ms");
			return bestMove;
		},

		minMax : function(fields, color, depth, flag){
			var moves = Moves.getMoves(fields, color);
			if(flag)
				var bestValue = -1000;
			else var bestValue = 1000;

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
				if(flag)
					var nextFlag = false;
				else var nextFlag = true;
				
				if(depth == 0)				
					value = this.evaluation(newFields, color);
				else value = this.minMax(newFields, Moves.opositColor(color), depth-1, nextFlag);		
				if(value > bestValue){
					bestValue = value;
				}
			}
			this.count++;
			return bestValue;			
		},

		evaluation : function(fields, color){
			// wyliczam wynik dla białego
			var value = 0;
			for(i in fields){
				var field = fields[i];
				if(field.isWhite()){
					if(field.isQueen()){
						value += 5;
					}else{
						value += 2;		
					}
				} else if (field.isBlack()){
					if(field.isQueen()){
						value -= 5;
					}else{
						value -= 2;		
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
