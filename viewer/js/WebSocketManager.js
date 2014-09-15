var WebSocketManager = Class.create();


WebSocketManager.prototype = {
  initialize: function(uri, service, outputObject, delay) {
    this.outputObject = outputObject;
    this.service = service;
    this.socket = new WebSocket(uri);
    this.socket.onopen = function() {
      console.log('socket ouverte');
      this.sendMessage(this.service);
    }.bind(this);
    this.socket.onclose = function() {
      console.log('socket fermée');
    }
    this.socket.onerror = function() {
      console.log('Une erreur est survenue');
    }
    this.socket.onmessage = function(msg) {
      try { //tente de parser data
        data = JSON.parse(msg.data);
      } catch (exception) {
        data = msg.data
      }
      console.log(data);
      if (this.outputObject.addData(data)) {
        setTimeout(function() {
          this.sendMessage(this.service)
        }.bind(this), delay);
      }
    }.bind(this);
  },
  sendMessage: function(message) {
    console.log(message)
    if(this.outputObject.getParameter){
      message += ' ' + this.outputObject.getParameter();
      console.log('add parameter :' + message)
    }
    this.socket.send(message);
  }
};