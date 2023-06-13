  var datas=new Array();
  var tag =0;
  var put = '';
  var datastuck = new Array();
  var id = new Array();
  var myChart;
  async function pickport(){   
    myChart=  echarts.init(document.getElementById('main'));
////////////////串口部分////////////////////////////////////////////
const port = await navigator.serial.requestPort();
await port.open(
    { baudRate: 115200/////波特率设置
   }
                );
          const textDecoder = new TextDecoderStream('UTF-8');
          const readableStreamClosed = port.readable.pipeTo(textDecoder.writable);
          const reader = textDecoder.readable.getReader();
////////////////读取串口///////////////////////////////////////////////////
  while(1){
    const { value, done } = await reader.read();
    var slic=new Array();
    slic =String(value).split("");
    //console.log("slic: ",slic);//浏览器F12控制台输出当前串口读取到的数据，去掉双斜杠启用
    datas=datas.concat(slic); 
/////////////////图表初始化////////////////////////////////////////////////
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
          data:[],
          name: "id",////X轴单位
          axisLabel:{
            fontSize:30,
            fontFamily: "serif",
          },
      },
      yAxis: {name: "11111111111",///y轴单位
      axisLabel:{
        fontSize:30,////字体大小
      },
    },
      dataZoom:{  
          type:"inside",
          filterMode: 'filter',
          height: '100%',
      },
      series: [{
          type: 'line',
          data:[],
          smooth:false,
      }]
  });
////////////////////////////////////////////////////////////////////////////
    if(slic.includes('#')){
      for(;datas[tag]!='#'&& tag<datas.length;tag++){
      put +=datas[tag];
    }
    tag++;
    //console.log("tag: ",tag);
    datastuck.push(Number(put));//数据分割入组
    put='';
    id.push(id.length); 
////////////////////////更新图表///////////////////////////////////////
    myChart.setOption({
      xAxis: {
      data: id
             },
         series: [
            {
            data: datastuck
            }
   ]
 });
    }
           
    //console.log("datas",datas); //所有已读字符
    //console.log("put:",put);     //最后一个数据 
    //console.log("datastuck: ",datastuck);//全部数据
    }
    
    }