var checkers;

function jsCheckersStart() {
	log("Matrix checkers\n");
	checkers = new Checkers();
	checkers.init();
};

Checkers = function() {
	this.view;
	this.images;
	this.AI;
};

Checkers.prototype = {
	init : function() {
		this.images = new Images();
		this.images.loadImages(this);
	},

	init2 : function() {
		this.view = new View();
		this.model = new Model();
		this.view.setImages(this.images);
		this.view.initKineticStageAndLayers();
		this.view.drawBoard();
	},

	initNewGame : function(){
		this.model.init();
		this.view.drawPawns(this.model.fields);
	},

	setPlayer: function(color, algorithm){
		log("color: "+color);
		this.player = new Player();
		this.player.setColor(color);
		this.player.setAI(new MinMaxAI());
//		this.player.setAI(new RandomAI());
		//log("setPlayer: "+this.player.color);
	},

	makeJsMove: function(){
		var fields = this.model.getFields();
		this.player.makeMove(fields);
	},

	makeNaClMove: function(move){
		move = move.split(',');
		var fields = this.model.getFields();
		var from = parseInt(move[0]);
		var to = parseInt(move[1]);	
	
		var beatingList = [];
		for(var i = 2; i<move.length; i++)
			beatingList.push(parseInt(move[i]));
	
		var opositColor = Moves.opositColor(this.player.color);
		Moves.move(fields, from, to, beatingList, opositColor);

		for(i in beatingList){
			checkers.view.deleteFigure(beatingList[i]);
		}	
		checkers.view.moveFigure(from, to);
	}

};
