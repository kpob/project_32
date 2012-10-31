naclModule = null;  // Global application object.
statusText = 'NO-STATUSES';

String.prototype.startsWith = function(needle){
    return(this.indexOf(needle) == 0);
};

function extractSearchParameter(name, def_value) {
  var nameIndex = window.location.search.indexOf(name + "=");
  if (nameIndex != -1) {
    var value = location.search.substring(nameIndex + name.length + 1);
    var endIndex = value.indexOf("&");
    if (endIndex != -1)
      value = value.substring(0, endIndex);
    return value;
  }
  return def_value;
}

function createNaClModule(name, tool, width, height) {
  var listenerDiv = document.getElementById('listener');
  var naclModule = document.createElement('embed');
  naclModule.setAttribute('name', 'nacl_module');
  naclModule.setAttribute('id', 'nacl_module');
  naclModule.setAttribute('width', width);
  naclModule.setAttribute('height',height);
  naclModule.setAttribute('src', tool + '/' + name + '.nmf');
  naclModule.setAttribute('type', 'application/x-nacl');
  listenerDiv.appendChild(naclModule);
}

function moduleDidLoad() {
  naclModule = document.getElementById('nacl_module');
}

function pageDidLoad(name, tool, width, height) {
  if (naclModule == null) {
    width = 0; 
    height = 0; 
    createNaClModule(name, tool, width, height)
  } else {
  }
}

function handleMessage(message_event) {
	var input = document.getElementById('logField');
	var msg = message_event.data;
	if(typeof(msg) == 'string') {
		if(msg.startsWith("setPlayers")){
			msg = msg.split(':');
			decodeSetPlayers(msg[1]);	
		}
		else if(msg.startsWith("newGame")){
			newGame();
		}
		else if(msg.startsWith("jsMove")){
			if(!stop)
				setTimeout(function(){
				//	log("timeout js");
					makeMove();
				}, 500);
		}
		else if(msg.startsWith("move")){
			setTimeout(function(){
			//	log("timeout nacl");
				makeNaClMove(msg.split(':')[1]);
			}, 250);
		}
		else if(msg.startsWith("board")){
			var board = msg.split(':')[1];
			var lines = board.split('\n');
			for(var l=0; l<8; l++){
				var elems = lines[l].split(' ').reverse().join(' ');
				log(elems);
			}
		}else if(msg.startsWith('endGame')){
			
			setTimeout(function(){
				alert('GAME OVER');
			}, 1000);
		}
		else{
			log("log:\n"+msg);
		}
	}

}


function decodeSetPlayers(msg){
	var splitMsg = msg.split(',');

	var player1 = {
		color: splitMsg[0],
		lang: splitMsg[1],
		algorithm: splitMsg[2]
	};

	var player2 = {
		color: splitMsg[3],
		lang: splitMsg[4],
		algorithm: splitMsg[5]
	};
	log("nacl: setPlayers");

	if(player1.lang == "js")
		checkers.setJSPlayer(player1.color, player1.algorithm);
	if(player2.lang == "js")
		checkers.setJSPlayer(player2.color, player2.algorithm);
}

function newGame(){
	log("nacl: newGame");
	naclModule.postMessage('printBoard');
}

function setPlayersToNaCl(){
	naclModule.postMessage('setPlayers:black,js,random,white,nacl,random');
	log("js: setPlayers");
}

function sendNewGameToNaCl(){
	 naclModule.postMessage('newGame');
	log("js: newGame");
}

function makeMove(){
//	log("JSMove");
	var fields = checkers.controler.getFields();
	var moves = Moves.getMovesForBlack(fields);
	//log("moves length: "+moves.length);
//	for(m in moves){
//		log(m+") "+moves[m].from+"->"+moves[m].to);
//	}
//	log();
	if(moves.length > 0){
		var moveNr = Math.floor(Math.random()*moves.length);
		var beatingList = [];
			//jeśli przynajmniej jednen ruch to bicie to mamy do czynienia
			//z samymi biciami
		var from = moves[moveNr].from;
		var to = moves[moveNr].to;
		log("js: "+from+"->"+to);
		//naclModule.postMessage("move:"+from+","+to);			
		
		if(moves[0].beating){
			for(i in moves[moveNr].beating){
				beatingList.push(moves[moveNr].beating[i].beat);
			}
		}
		Moves.moveBlack(fields, from, to, beatingList);
		for(i in beatingList){
			checkers.controler.view.deleteFigure(beatingList[i]);
		}
		checkers.controler.view.moveFigure(from, to);

		var movesForNacl = [];
		if(moves[0].beating){
			for(i in moves[moveNr].beating){
				var beat = moves[moveNr].beating[i];
				if(i == 0){
					movesForNacl.push({
						f : from,
						t : beat.end
					});
				}else{
					var beatPrev = moves[moveNr].beating[i-1];
					movesForNacl.push({
						f : beatPrev.end,
						t : beat.end
					});
				}
			}

			var move = "move:"+movesForNacl[0].f+","+movesForNacl[0].t;
			for(var s=1; s<movesForNacl.length; s++){
				move = move + ","+movesForNacl[s].f+","+movesForNacl[s].t;
			}
			log(move);
			naclModule.postMessage(move);				
		}else{
			movesForNacl.push({
						f : from,
						t : to
					});
			naclModule.postMessage("move:"+from+","+to);	
		}

	}
}

var stop = false;
function makeNaClMove(move){
	move = move.split(',');
	log("NaClMove: "+move[0]+"->"+move[1]);
	var fields = checkers.controler.getFields();
	var from = parseInt(move[0]);
	var to = parseInt(move[1]);	
	
	var beatingList = [];
	
	naclModule.postMessage("printBoard");
	for(var i = 2; i<move.length; i++)
		beatingList.push(parseInt(move[i]));
	
	Moves.moveWhite(fields, from, to, beatingList);

	for(i in beatingList){
		checkers.controler.view.deleteFigure(beatingList[i]);
	}	
	checkers.controler.view.moveFigure(from, to);
}


