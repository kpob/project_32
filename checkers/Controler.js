	Controler = function(){
	// Elementy systemu
	this.view = {};
	this.model = {};
	
	this.from = {};
	this.figureSelected = false;
	
	//Gracze
	this.player = {};
};

Controler.prototype = {
		setView : function(view){
			this.view = view;
			this.view.setControler(this);
		},
		
		setModel: function(model){
			this.model = model;
		},
		
		setPlayer: function(color, algorithm){
			this.player = new Player();
			this.player.setColor(color);
			this.player.setAI(new RandomAI());
		},
		
		getFields : function() {
			return this.model.getFields();
		},
/*
		// Eventy
		onFigureClick : function(position){
//			this.from = position;
//			this.figureSelected = true;
//			this.move();
		},
		
		onSquareClick : function(position) {
//			this.move();
		}		
*/
};
