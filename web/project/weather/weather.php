<?php
$cityid = $_GET["cityid"];
$day = $_GET["day"];
//$more = $_GET["mo"];
//$little = $_GET["li"];
$key = 'key';

$url = 'https://devapi.qweather.com/v7/weather/'.$day.'d?location='.$cityid.'&key='.$key;  //  url和参数
$result = gzdecode(file_get_contents($url),50000);
//var_dump(json_decode($result, true));
$date = json_decode($result, true);
//echo $result;
echo $date["updateTime"];
echo '<br><br>';
echo $date["daily"][0]["fxDate"];
echo $date["daily"][0]["textDay"];
echo "temp: ";
echo $date["daily"][0]["tempMin"];
echo "--";
echo $date["daily"][0]["tempMax"];
echo "humidity";
echo $date["daily"][0]["humidity"];
//print_r($date["daily"][0]);
 
   // echo $row['id'] .'"'. $row['dev'] .'"'. $row['time'] .'"'.$row['tem'] .'"'.$row['hum'] ;


?>