<?php
$con = mysqli_connect('49.233.60.32','root','sU,:/sK&n%522@#');


mysqli_select_db($con,"test");
mysqli_set_charset($con, "utf8");
 
$sql="select max(id) from test_trans;"; 
$maxid = mysqli_fetch_array(mysqli_query($con,$sql))[0]; 
//echo $maxid;

$sql="select min(id)from test_trans;";
$minid = mysqli_fetch_array(mysqli_query($con,$sql))[0];
//echo $minid;

$sql="select time from test_trans where id=(select min(id)from test_trans);";
$mintime = mysqli_fetch_array(mysqli_query($con,$sql))[0];
$sql="select time from test_trans where id=(select max(id)from test_trans);";
$maxtime = mysqli_fetch_array(mysqli_query($con,$sql))[0];

if (empty($maxid)) {echo "date error!";}
if (empty($minid)) {echo "date error!";}
else{
    $date = "{$maxid}"."*"."$minid"."*"."{$mintime}"."*"."{$maxtime}";
    echo($date) ;
}

mysqli_close($con);
?>