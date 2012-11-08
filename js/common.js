naclModule = null;  // Global application object.
statusText = '';

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
			//if(!stop)
				setTimeout(function(){

					checkers.makeJsMove();
				}, 1000);
		}
		else if(msg.startsWith("move")){
	//		setTimeout(function(){
				log("nacl");
				checkers.makeNaClMove(msg.split(':')[1]);
	//		}, 2000);
		}
		else if(msg.startsWith("board")){
			var board = msg.split(':')[1];
			var lines = board.split('\n');
			for(var l=0; l<8; l++){
				var elems = lines[l].split(' ').reverse().join(' ');
			}
		}
		else if(msg.startsWith('endGame')){
			log("endGameFromNaCl");
		}
		else if(msg.startsWith('zmiana')){
			naclModule.postMessage('naclMove');
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
	//log("nacl: setPlayers");

	if(player1.lang == "js")
		checkers.setPlayer(player1.color, player1.algorithm);
	if(player2.lang == "js")
		checkers.setPlayer(player2.color, player2.algorithm);
}

function newGame(){
	//log("nacl: newGame");
	//naclModule.postMessage('printBoard');
}

function setPlayersToNaCl(){
	naclModule.postMessage('setPlayers:black,js,minmax,white,nacl,minmax');
	//log("js: setPlayers");
}

function sendNewGameToNaCl(){
	checkers.initNewGame();
	naclModule.postMessage('newGame');
	//log("js: newGame");
}
var stop = false;

function clearLog() {
	var input = document.getElementById('logField');
	input.innerHTML = "";
}

function printBoard(){
	naclModule.postMessage('printBoard');
}

