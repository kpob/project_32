View = function() {
	// System elements
	this.images = {};
	this.controler = {};

	// Kinetic stuff
	this.stage = {};
	this.boardLayer = {};
	this.messageLayer = {};
	this.figuresLayer = {};
	this.squareList = [];
	this.figuresList = [];

	// Config
	this.squareSize = 60;
	this.width = this.squareSize * 8;
	this.height = this.squareSize * 8;
};

View.prototype = {
	setImages : function(images) {
		this.images = images;
	},

	setControler : function(controler) {
		this.controler = controler;
	},

	initKineticStageAndLayers : function() {
		this.stage = new Kinetic.Stage({
			container : 'container',
			width : this.width,
			height : this.height
		});

		this.boardLayer = new Kinetic.Layer();
		this.stage.add(this.boardLayer);

		this.figuresLayer = new Kinetic.Layer();
		this.stage.add(this.figuresLayer);
	},

	drawBoard : function() {
		for ( var row = 0; row < 8; row++) {
			for ( var column = 0; column < 8; column++) {
				if ((row % 2 == 0 && column % 2 == 0)
						|| (row % 2 != 0 && column % 2 != 0)) {
					this.drawBlackSquare(row, column);
				} else {
					this.drawWhiteSquare(row, column);
				}
			}
		}
		this.boardLayer.draw();
	},

	drawWhiteSquare : function(row, column) {
		var square = new Kinetic.Image({
			x : row * this.squareSize,
			y : (7 - column) * this.squareSize,
			image : this.images.getImage("whiteField"),
			width : this.squareSize,
			height : this.squareSize

		});
		this.boardLayer.add(square);
	},

	drawBlackSquare : function(row, column) {
		var square = new Kinetic.Image({
			x : row * this.squareSize,
			y : (7 - column) * this.squareSize,
			image : this.images.getImage("blackField"),
			width : this.squareSize,
			height : this.squareSize
		});
		square.position = Math.floor((row + column * 8) / 2);

		var self = this;
		square.on('click', function() {
			self.controler.onSquareClick(this.position);
		});
		this.squareList[square.position] = square;
		this.boardLayer.add(square);
	},

	drawPawns : function(fields) {
		var whitePawn = this.images.getImage("whitePawn");
		var blackPawn = this.images.getImage("blackPawn");
		var whiteQueen = this.images.getImage("whiteQueen");
		var blackQueen = this.images.getImage("blackQueen");
		for (i in fields) {
			if (!fields[i].isFree()) {
				var field = fields[i];
				var figure;
				if (field.isWhite()) {
					if (field.isQueen()) {
						figure = this.createFigure(i, whiteQueen);
						figure.color = "white";
					} else {
						figure = this.createFigure(i, whitePawn);
						figure.color = "white";
					}
				} else if (fields[i].isBlack()) {
					if (field.isQueen()) {
						figure = this.createFigure(i, blackQueen);
						figure.color = "black";
					} else {
						figure = this.createFigure(i, blackPawn);
						figure.color = "black";
					}
				}
				this.figuresList.push(figure);
				this.figuresLayer.add(figure);
			}
		}
		this.figuresLayer.draw();
	},

	createFigure : function(position, image) {
		var XY = this.getXY(position);
		var figure = new Kinetic.Image({
			x : XY.x,
			y : XY.y,
			image : image,
			width : this.squareSize,
			height : this.squareSize
		});
		figure.position = position;

		var self = this;
		figure.on('click', function() {
			self.controler.onFigureClick(this.position);
		});
		return figure;
	},

	getXY : function(position) {
		var square = this.squareList[position];
		var pos = square.getPosition();
		return pos;
	},

	moveFigure : function(from, to) {
		var figure = this.getFigure(from);
		var XY = this.getXY(to);
		figure.position = to;

		var self = this;
		figure.transitionTo({
			x : XY.x,
			y : XY.y,
			width: this.squareSize,
			height : this.squareSize,
			duration : 1 / 3,
			callback : function() {
				if (figure.color == "white" && (figure.position == 31 || figure.position == 30
						|| figure.position == 29 || figure.position == 28)) {
					figure.setImage(self.images.getImage("whiteQueen"));
				}
				if (figure.color == "black" && (figure.position == 0 || figure.position == 1
						|| figure.position == 2 || figure.position == 3)) {
					figure.setImage(self.images.getImage("blackQueen"));
				}
			}
		});
	},

	getFigure : function(position) {
		var list = this.figuresList;
//		log("szukana: "+position);
//		for (j in list)
//			log(j+") "+list[j].position);	
		for (i in list) {
			if (list[i].position == position) {
				return list[i];
			}
		}
	},

	deleteFigure : function(position) {
		log("to delete :"+position);
		var figuresList = this.figuresList;
		var counter = 0;
		for (i in figuresList) {
			if (figuresList[i].position == position) {
				counter = i;
			}
		}

		var squareToRemove = figuresList[counter];
		squareToRemove.transitionTo({
			opacity : 0,
			duration : 1/10,
			callback : function() {
				squareToRemove.remove();
			}
		});
		figuresList.splice(counter, 1);
		this.figuresLayer.draw();
	},

	listFigures : function() {
		log("List figures:");
		var list = this.figuresList;
		for (i in list) {
			log(list[i].position);
		}
	}
};  	
