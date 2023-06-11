var http = require('http');
var mysql = require('mysql');
var querystring = require('querystring');
var connection = mysql.createConnection({     
  host     : '49.233.60.32',       
  user     : 'www_sektech_fit',              
  password : 'iA7jNz3T3sRefkCF',       
  port: '3306',                   
  database: 'test' 
}); 

connection.connect();

http.createServer(function (req, res) {
  var body = "";
  req.on('data', function (chunk) {
    body += chunk;
  });
req.on('end',function(){

var hum = (Number(body)%1000);
var tem =(Number(body-hum)/1000)/10;
var hum1 =hum/10;
var  addSql = 'INSERT INTO testchart(id,time,tem,hum) VALUES(0,CURRENT_TIMESTAMP,?,?)';
var  addsqlParams = [tem,hum1];
connection.query(addSql,addsqlParams);
});

}).listen(3000);

