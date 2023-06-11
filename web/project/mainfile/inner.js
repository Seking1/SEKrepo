///////////////////////////////////////////////////////////////////////
function showDateTime(){
    setInterval(function(){
    var sWeek=new Array("日","一","二","三","四","五","六"); 
    var myDate=new Date(); 
    var sYear=myDate.getFullYear(); 
    var sMonth=myDate.getMonth()+1; 
    var sDate=myDate.getDate(); 
    var sDay=sWeek[myDate.getDay()]; 
    var h=myDate.getHours(); 
    var m=myDate.getMinutes(); 
    var s=myDate.getSeconds();
    document.getElementById("date").innerHTML=("日期："+sYear+"年"+sMonth+"月"+sDate+"日"+"星期"+sDay+"<br/>");
    h = formatTwoDigits(h); 
    m = formatTwoDigits(m); 
    s = formatTwoDigits(s); 
    document.getElementById("msg").innerHTML=(h+":"+m+":"+s+"<br/>");
    GetDHT();
},1000);
}
window.onload=showDateTime;
function formatTwoDigits(s) {
    if (s<10)
        return "0"+s;
    else
        return s;
}
///////////////////////////////////////////////////////////////////
function iddate(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var getid =this.responseText;
            var gi = getid.split("*");
            console.log(gi);
            var maxid=gi[0];
            console.log(maxid);
            var minid = gi[1];
            console.log(minid);
            document.getElementById("dateidNumber").innerHTML = minid;
            var maxtime = gi[3];
            var mintime = gi[2];
            document.getElementById("timespanmin").innerHTML = mintime;
            document.getElementById("timespanmax").innerHTML = maxtime;
        }
      };
      xhttp.open("GET", "idget.php", false);
      xhttp.send();
    }
function GetDHT() {
    var idNumber= document.getElementById("dateidNumber").innerHTML; 
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            maindate(this.responseText);
            //console.log(this.responseText);
        }
      };
      idNumber = String (idNumber);
      xhttp.open("GET", "database.php?idNumber="+idNumber, false);
      xhttp.send();
    }
function maindate(response) {
      var DHTT = 0;
      var DHTH = 0;
      var time = ""; 
      var dev = "";
      var dhtdatearray=new Array(5);
      dhtdatearray = response;
      //console.log('rep',response);
      //console.log('DHT',dhtdatearray);
      var DHT = dhtdatearray.split('"');
      //console.log('DHT',DHT);
      time = DHT[2];
      dev = DHT[1];
      //console.log('time',time);
      DHTT = Number(DHT[3]);
      DHTH = Number(DHT[4]);
      //console.log(Number(DHT[0])+1);
      document.getElementById("DHTT").innerHTML=DHTT;
      document.getElementById("DHTH").innerHTML=DHTH;
      document.getElementById("time").innerHTML=time;
      document.getElementById("dev").innerHTML=dev;
      document.getElementById("dateidNumber").innerHTML=Number(DHT[0])+1;
}
//////////////////////////////////////////////////////////////////
var city = "";
function checkcity() {
    var html = document.getElementById("cityline").innerHTML;
    html.innerHTML="";
    var cityname = document.getElementById("cityname").value; 
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var cityline = String(this.responseText);
            console.log(cityline);
            city = cityline.split('#');
            console.log(city);
            for(var x=0;x<city.length;x++){
              var html = document.getElementById("cityline").innerHTML;
            document.getElementById("cityline").innerHTML=html+"<li onclick='weather("+x+")'>"
                                  +String(city[x])+"</li>";}
            //console.log(this.responseText);
            
        }
      };
      xhttp.open("GET", "../weather/city.php?cityname="+cityname, false);
      xhttp.send();
    }

    
function weather(x) {
      var cityid = String(city[x]).split('*');
      var xhttp = new XMLHttpRequest();
     xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var weather = document.getElementById("weather");
            weather.innerHTML = this.responseText;                      
        }
     };
      xhttp.open("GET", "../weather/weather.php?cityid="+cityid[1]+"&day=3", false);
      xhttp.send();
    }