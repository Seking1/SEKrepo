  var datas=new Array();
  var tag =0;
  var put = '';
  var data={
    "temperature":[24.86,24.86,24.86,24.86,24.86,24.86,24.86,24.86,24.86,24.86,24.86],
    "humidity":[48.17,48.17,48.17,48.17,48.17,48.17,48.17,48.17,48.17,48.17,48.17],
  };
  var datastuck = new Array();
  var id = new Array();
  var myChart;
  function pickport(){   
    myChart=  echarts.init(document.getElementById('main'));
    myChart.setOption({
      title: {
        text: "Main Title",///////标题/////////////////////////////
        left: "center",
        top: "top",
        textStyle: {
          fontSize: 50//字体大小
        },
      },
      tooltip: { trigger: "axis"},
      xAxis: {
          data:[1,2,3,4,5,6,7,8,9,10],
          name: "id",////X轴单位
          axisLabel:{
            fontSize:30,
            fontFamily: "serif",
          },
          nameTextStyle :{
            fontSize: 30
          }
      },
      yAxis: {
        type:"value",
        data:[],
        name: "data",///y轴单位
      axisLabel:{
        fontSize:30,////字体大小
      },
      nameTextStyle :{
        fontSize: 30
      }
    },
      dataZoom:{  
          type:"inside",
          filterMode: 'filter',
          height: '100%',
      },
      series: [{
          type: 'line',
          data:data["temperature"],
          smooth:false,
      },
      {
        type: 'line',
        data:data["humidity"],
        smooth:false,
    }
    ]
  });

    myChart.setOption(
      {
        yAxis:{
          data:data,
        }
      }
    );
    }
    
  