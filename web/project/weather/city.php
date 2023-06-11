<?php
$cityname = urlencode($_GET["cityname"]);
//$adm = $_GET["admname"];
//$day = $_GET["day"];
$key = 'key';

$url = 'https://geoapi.qweather.com/v2/city/lookup?location='.$cityname.'&key='.$key;
$result = gzdecode(file_get_contents($url),500000);
//var_dump(json_decode($result, true));
$date = json_decode($result, true);
//echo $result;
$citycount = count($date["location"]);
$cityline="";
for ($x = 1 ;$x<$citycount;$x++){
    $cityline = $cityline.$date["location"][$x]["name"].'*'.$date["location"][$x]["id"].'#';
}
$cityline = chop($cityline,"#");
echo $cityline;
   // echo $row['id'] .'"'. $row['dev'] .'"'. $row['time'] .'"'.$row['tem'] .'"'.$row['hum'] ;


?>