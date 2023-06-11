<?php
$nameErr =  $emailErr = $paswordErr = "";
$name =$email =$password = "";
if (empty($_POST["name"])) {
      $nameErr = "名字是必须的。";
   } else {
      $name = test_input($_POST["name"]);
}
if (empty($_POST["email"])) {
      $emailErr = "邮箱是必须的。";
   } else {
      $email = test_input($_POST["email"]);
   }

   if (empty($_POST["password"])) {
      $passwordErr = "密码是必须的。";
   } else {
      $password = test_input($_POST["password"]);
   }

function test_input($data) {
   $data = trim($data);
   $data = stripslashes($data);
   $data = htmlspecialchars($data);
   return $data;}
   ?>
   <?php
echo "<!DOCTYPE HTML>
<html>
	<head>
    <meta charset='UTF-8'>
    <link rel='stylesheet' type='text/css' href='register.css'>
    <title>基于Labview和单片机的温湿度监测网络平台</title>
   <script type = 'text/javascript' src = 'register.js'></script>
   <style>
    a:link {color:#000000;}  
a:visited {color:#000000;}  
a:hover {color:#D8BFD8;}  
a:active {color:#D8BFD8;}</style>
	</head>
    <body>
    <div id='mainpagediv' style='background-color:ghostwhite;'>
        <a href='https://www.ahu.edu.cn/' target='_black' id='logo'><img src='AHU.png' alt='安徽大学' style='    margin-top: 13px;'></a>
        <ul style='display: flex;list-style: none;margin: auto;float: right;flex-direction: row;'>
   <li style='margin: auto;float: right; margin-left: -50%;'> 
   <h2 id= 'titlename'>基于Labview和单片机的温湿度监测网络平台</h2></li> 
   <li style='margin-top: auto;float: right;margin-bottom: auto;margin-right: 2%;'> <a href='/project/mainfile/index.html' id='user'
    style = 'text-decoration: none;'>主页</a></li>
   <li style='margin-top: auto;float: right;margin-bottom: auto;margin-right: 2%;'> <a href='/project/register/register.php' id='user'
    style = 'text-decoration: none;'>注册</a></li>
    </div>
	<h2>注册页面</h2>
	<form method='post'>
   用户名: <input type='text' autocomplete='用户名' name='name' value= '";?>
   <?php echo $name; echo "'>";?>
   
   <?php echo "<span class= 'error'>"; echo $nameErr;echo "</span>
   <br><br>
   E-mail: <input type='text' name='email' autocomplete='email' value='"; echo $email;echo"'>"; 
    echo "<span class='error'>* ";echo $emailErr; echo "</span>
   <br><br>
   密码: <input type='text' name='password' autocomplete='password' value='"; echo $password;echo "'>";
   echo "<br><br>
   <input type='submit' name='submit' value='Submit'> 
</form>";?>

<?php
$con = mysqli_connect('49.233.60.32','root','sU,:/sK&n%522@#');
//if (!$con)
//{
 //   die('Could not connect: ' . mysqli_error($con));
//}
mysqli_select_db($con,"projectuser");
mysqli_set_charset($con, "utf8");
$str ="SELECT MAX(Tid) FROM user;";
$tid =mysqli_fetch_array(mysqli_query($con,$str));   
$Tid = $tid[0]+1;
$sql="INSERT INTO user VALUES ({$Tid},?,?,?);";
$stmt = mysqli_stmt_init($con);
if (mysqli_stmt_prepare($stmt, $sql) && !(empty($name))&&!(empty($email))&&!(empty($password))) {
        mysqli_stmt_bind_param($stmt, 'sss', $name, $password, $email);
        $password = sha1($password);
        mysqli_stmt_execute($stmt);
        $check = "SELECT Tid FROM user WHERE Tid = {$Tid};";
        if(!empty(mysqli_query($con,$check))){echo "注册成功,Tid:",$Tid,"<br>用户名:",$name;};
            mysqli_close($con);
    }

?>
<?php
echo"
</body>
</html>";
?>