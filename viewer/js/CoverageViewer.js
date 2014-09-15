var CoverageViewer = Class.create();


CoverageViewer.prototype = {
  initialize: function(idContainer) {
    this.canvas = document.getElementById(idContainer);
    this.contexte = this.canvas.getContext("2d");
  },
  addData: function(data) {
    this.contexte.clearRect ( 0 , 0 , this.canvas.width , this.canvas.height );

    var off = document.createElement('canvas');
    off.width = 500;
    off.height = this.canvas.height;
    var ctx = off.getContext('2d');
    ctx.beginPath();
    ctx.rect(0, 0, 500, this.canvas.height);
    ctx.fill();

    var coeff = this.canvas.width / data[data.length-1].fin;
    console.log("taille : " + data.length);
    for (var i = data.length - 1; i >= 0; i--) {
       this.contexte.drawImage(off, data[i].debut*coeff, 0, (data[i].fin - data[i].debut)*coeff, 100);
    };


    console.log('over');
    return data.length != 1;

  }
};