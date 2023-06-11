function musicid(){
    var musicidn = document.getElementById("musicid").value;
    console.log(musicidn);
    var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            var date =JSON.parse(this.responseText);
            console.log(date);
            var urld = date.data[0].url;
            console.log(urld);
            var box=document.getElementById("musicb");
            box.src = urld;
            document.getElementById("musicbox").load();
            lyric(musicidn);
        }
      };
      xhttp.open("GET", "http://49.233.60.32:4001/song/url?id="+musicidn, false);
      xhttp.send(); 
}
function lyric(musicidn){
     var xhttp = new XMLHttpRequest();
     xhttp.onreadystatechange = function() {
       if (this.readyState == 4 && this.status == 200) {
        console.log(this.responseText);
        var date =JSON.parse(this.responseText);
        //console.log(date);
        var urld = date.data[0].url;
        //console.log(urld);
        var box=document.getElementById("lyric");
        box.innerHTML = this.responseText;
      }
      };
  xhttp.open("GET", "http://49.233.60.32:4001/lyric?id="+musicidn, false);
  xhttp.send(); 
}