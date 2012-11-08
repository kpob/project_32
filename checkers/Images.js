Images = function() {
	this.imagesPaths = [ {
		name : "whiteField",
		path : "img/whiteField.png",
	}, {
		name : "blackField",
		path : "img/blackField.png",
	}, {
		name : "whitePawn",
		path : "img/whitePawn.png",
	}, {
		name : "blackPawn",
		path : "img/blackPawn.png",
	}, {
		name : "selectedField",
		path : "img/selectedField.png",
	}, {
		name : "whiteQueen",
		path : "img/whiteQueen.png",
	}, {
		name : "blackQueen",
		path : "img/blackQueen.png",
	}, {
		name : "board",
		path : "img/1.png",
	} ];
	this.images = [];
	this.count = 0;
};

Images.prototype = {

	loadImages : function(callback) {
		for (i in this.imagesPaths) {
			this.loadImage(this.imagesPaths[i].name, this.imagesPaths[i].path,
					callback);
		}
	},

	loadImage : function(name, path, gameObj) {
		var self = this, imgObj = new Image();

		imgObj.onload = function() {
			self.count++;
			self.images.push({
				name : name,
				image : imgObj
			});
			
			if (self.count == self.imagesPaths.length) {
				gameObj.init2();
			}
		};
		imgObj.src = path;
	},

	getImage : function(name) {
		var images = this.images;
		for (i in images) {
			if (images[i].name == name) {
				return images[i].image;
			}
		}
	}
};
