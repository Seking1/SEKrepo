<?php
$idNumber = $_GET['idNumber'];
$con = mysqli_connect('49.233.60.32','root','sU,:/sK&n%522@#');

mysqli_select_db($con,'test');
mysqli_set_charset($con, 'utf8');
 
$sql="SELECT id,dev,time,dht22_tem,dht22_hum FROM test_trans WHERE id = {$idNumber}";
$result = mysqli_query($con,$sql); 


if (empty($result)) {echo 'no dates!';}
else{
while($row = mysqli_fetch_array($result))
{   
    echo $row['id'] .'"'. $row['dev'] .'"'. $row['time'] .'"'.$row['dht22_tem'] .'"'.$row['dht22_hum'] ;
}
}

mysqli_close($con);
?>