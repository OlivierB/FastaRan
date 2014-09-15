var NucleotideSinger = Class.create();


NucleotideSinger.prototype = {
  initialize: function(idContainerVolume, idContainerDisplay) {
    this.notes = {
      'AA': 261,
      'AT': 277,
      'AG': 293,
      'AC': 311,
      'TA': 329,
      'TT': 349,
      'TG': 369,
      'TC': 392,
      'GA': 415,
      'GT': 440,
      'GG': 440,
      'GC': 466,
      'CA': 493,
      'CT': 523,
      'CG': 554,
      'CC': 587
    };

    this.context = new window.AudioContext();

    this.osc = this.context.createOscillator();
    this.osc.frequency.value = 222;
    this.osc.connect(this.context.destination);
    this.osc.start(0);

    this.gainNode = this.context.createGain();
    // Connect the source to the gain node.
    this.osc.connect(this.gainNode);
    // Connect the gain node to the destination.
    this.gainNode.connect(this.context.destination);
    this.gainNode.gain.value = -.75;

    this.range = document.getElementById(idContainerVolume);
    this.range.addEventListener("input", this.setVolume.bind(this));

    this.displayNucleos = document.getElementById(idContainerDisplay);

    this.cursor = 0;
  },
  addData: function(data) {
    this.displayNucleos.innerHTML = data;
    this.osc.frequency.value = this.notes[data];
    this.cursor += 2;
    return true;
  },
  setVolume: function() {
    var fraction = parseInt(this.range.value) / parseInt(this.range.max);
    this.gainNode.gain.value = fraction * fraction - 1;
    console.log(fraction * fraction - 1);
  },
  getParameter : function(){
    return this.cursor;
  }
};