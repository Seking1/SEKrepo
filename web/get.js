var mysql = require('mysql');
var express = require('express');
var app = express(); 

var connection = mysql.createConnection({
    host:'49.233.60.32',
    user:'www_sektech_fit',
    password:'iA7jNz3T3sRefkCF',
    port:'3306',
    database:'test'
})
 
connection.connect(); 
 
 app.get('/',(req,res)=>{
           //将数据库信息返回前台
           res.setHeader("Access-Control-Allow-Origin", "*");
            res.send({'tem':11.1,'num':22.2});
 
            console.log('正在访问接口……');

             console.log(req.query);
          }).listen(3003)
var  sql = 'SELECT tem,hum FROM testchart WHERE id = 500';
var str = '';
connection.query(sql,  (error, results, fields)=> {
    if (!error) {
        app.get('/',(req,res)=>{
           //将数据库信息返回前台
           //res.setHeader("Access-Control-Allow-Origin", "*");
            res.send({
    "tem":11.1,
    "num":22.2
});
 
            //console.log('正在访问接口……');
            // 打印前台数据
            // console.log(req.query);
          }).listen(3003)
        
    }})
