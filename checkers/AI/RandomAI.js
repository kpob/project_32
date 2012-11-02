RandomAI = function(){
};

RandomAI.prototype = {
		pickMove : function(fields, color){
			var moves = Moves.getMoves(fields, color);
			var rand = Math.floor(Math.random()*moves.length);
			return moves[0];
		},
		
		say : function(){
			log("random Dude");
		}
};
