function checkcity() {
   var cityname = document.getElementById("cityname").value; 
     var xhttp = new XMLHttpRequest();
     xhttp.onreadystatechange = function() {
       if (this.readyState == 4 && this.status == 200) {
           document.getElementById("cityline").innerHTML=this.responseText;
           //console.log(this.responseText);
       }
     };
     idNumber = String (idNumber);
     xhttp.open("GET", "../weather/city.php?cityname="+cityname, false);
     xhttp.send();
   }