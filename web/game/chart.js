function pickport() {
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