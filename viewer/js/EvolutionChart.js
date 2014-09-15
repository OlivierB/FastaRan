var EvolutionChart = Class.create();


EvolutionChart.prototype = {
  initialize: function(idContainer, title, maxValue) {
    this.dataSet = [];
    this.maxValue = maxValue;
    this.chart = new CanvasJS.Chart(idContainer, {

      title: {
        text: title
      },
      axisX: {
        valueFormatString: "HH:mm:ss"
      },
      axisY: {
        maximum: maxValue
      },
      data: [{
        type: "line",

        dataPoints: this.dataSet
      }]
    });

    this.chart.render();
  },
  addData: function(data) {

    this.dataSet.push({
      x: new Date(),
      y: parseInt(data)
    });
    this.chart.render();
    if (!this.maxValue || parseInt(data) < this.maxValue) {
      return true;
    } else {
      return false;
    }

  }
};