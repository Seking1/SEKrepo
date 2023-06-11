<?php
$constate = $nameErr = $registerstate = $emailErr = $paswordErr = "";
$name = $email = $gender = $comment = $website = "";

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
   return $data;
}
?>