RandomAI = function(){
};

RandomAI.prototype = {
		pickMove : function(fields, possibleMoves, color){
			var rand = Math.floor(Math.random()*possibleMoves.length);
			return rand;
		},
		
		say : function(){
			log("random Dude");
		}
};