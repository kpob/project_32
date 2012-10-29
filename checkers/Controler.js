	Controler = function(){
	// Elementy systemu
	this.view = {};
	this.model = {};
	
	this.from = {};
	this.figureSelected = false;
	
	//Gracze
	this.whitePlayer = {};
	this.blackPlayer = {};
	
	this.whitePlayerNow = true;
};

Controler.prototype = {
		setView : function(view){
			this.view = view;
			this.view.setControler(this);
		},
		
		setModel: function(model){
			this.model = model;
		},
		
		setWhitePlayer: function(whitePlayer){
			this.whitePlayer = whitePlayer;
			this.whitePlayer.setControler(this);
		},
		
		setBlackPlayer: function(blackPlayer){
			this.blackPlayer = blackPlayer;
			this.blackPlayer.setControler(this);
		},
		
		getFields : function() {
			return this.model.getFields();
		},

		// Eventy
		onFigureClick : function(position){
//			this.from = position;
//			this.figureSelected = true;
//			this.move();
		},
		
		onSquareClick : function(position) {
//			this.move();
		},
		
		move : function(){
			var self = this;
			if(this.whitePlayerNow){
				this.whitePlayerNow = false;
				setTimeout(function(){
					self.blackPlayer.makeMove();
				}, 1);
			}else{
				this.whitePlayerNow = true;
				setTimeout(function(){
					self.whitePlayer.makeMove();
				}, 1);
			}
		}		
};
