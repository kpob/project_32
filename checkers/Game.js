var checkers;

function gStart() {
	log("Matrix checkers\n");
	checkers = new Checkers();
	checkers.init();
};

Checkers = function() {
	this.view;
	this.images;
	this.controler;
};

Checkers.prototype = {
	init : function() {
		this.images = new Images();
		this.images.loadImages(this);
	},

	init2 : function() {
		this.controler = new Controler();
		this.view = new View();
		this.model = new Model();

		this.controler.setView(this.view);
		this.controler.setModel(this.model);

		this.view.setImages(this.images);
		this.view.initKineticStageAndLayers();
		this.view.drawBoard();

		// inicjalizacja planszy
		this.model.init();
		this.view.drawPawns(this.model.fields);
	},

	setJSPlayer : function (color, algorithmName){
		if(color == "white"){
			log("W");
			var whitePlayer = new Player();
			whitePlayer.setAI(new RandomAI());
			whitePlayer.setColor("white");
			this.controler.setWhitePlayer(whitePlayer);
		}else{
			log("B");
			var blackPlayer = new Player();
			blackPlayer.setColor("black");
			blackPlayer.setAI(new RandomAI());
			this.controler.setBlackPlayer(blackPlayer);
		}
	},
};
